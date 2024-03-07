#!/usr/bin/env bash

set -eo pipefail

TXT_RED="\e[31m"
TXT_CLEAR="\e[0m"

# Ensure we have the latest of the alternate branches
git fetch origin solution:solution
git fetch origin incorrect:incorrect

git tag -f starter-code 8b48c3b614ed27b026ba3a43116fd0e4df880758

echo -e "$TXT_RED"
echo "Running tests as submitted (sanity check)"
echo "========================================="
echo -e "$TXT_CLEAR"

coverage run -m pytest --timeout=120 || [ $? == 1 ]

mapfile -t STUDENT_STUDENT_PASSING < all_passed


echo -e "$TXT_RED"
echo "Checking coverage with submitted tests"
echo "======================================"
echo -e "$TXT_CLEAR"

python3 mark_coverage.py "${STUDENT_STUDENT_PASSING[@]}" > coverage_marks
coverage report


echo -e "$TXT_RED"
echo "Running our tests against submitted implementations"
echo "==================================================="
echo -e "$TXT_CLEAR"

rm -f implementation_marks
git checkout solution acronym_test.py dateadjust_test.py foo_test.py mono_test.py questions_test.py server_test.py 2> /dev/null
pytest --save-marks --timeout=120 || [ $? == 1 ]
git reset --hard HEAD &> /dev/null


echo -e "$TXT_RED"
echo "Running submitted tests against working implementation"
echo "======================================================"
echo -e "$TXT_CLEAR"

git checkout solution acronym.py dateadjust.py mono.py questions.py 2> /dev/null
if git show HEAD:dateadjust.py | grep 'strftime.*%d' > /dev/null
then
    echo "Making adjustment for leading zeroes"
    sed -i'' '/strftime/s/%-d/%d/g' dateadjust.py
fi
pytest --timeout=120 || [ $? == 1 ]
mapfile -t STUDENT_OURS_PASSING < all_passed

rm -f test_correct_marks
for exercise in ${STUDENT_OURS_PASSING[*]}
do
    if ! git diff -w --exit-code HEAD starter-code "$exercise"_test.py &> /dev/null
    then
        case $exercise in
        "mono") echo -n "mono_test_correct|1.5|" >> test_correct_marks;;
        "acronym") echo -n "acronym_test_correct|1.5|" >> test_correct_marks;;
        "dateadjust") echo -n "dateadjust_test_correct|2|" >> test_correct_marks;;
        "questions") echo -n "questions_test_correct|2.5|" >> test_correct_marks;;
        esac
    fi
done

git reset --hard HEAD &> /dev/null

echo -e "$TXT_RED"
echo "Running submitted tests against non-working implementation"
echo "=========================================================="
echo -e "$TXT_CLEAR"

git checkout incorrect acronym.py dateadjust.py foo.py mono.py questions.py 2> /dev/null
pytest --tb=no --timeout=120 || [ $? == 1 ]
mapfile -t STUDENT_OURS_BAD_PASSING < all_passed

rm -f test_incorrect_marks
for exercise in ${STUDENT_OURS_PASSING[*]}
do
    if ! [[ " ${STUDENT_OURS_BAD_PASSING[*]} " =~ ${exercise} ]]
    then
        if ! git diff -w --exit-code HEAD starter-code "$exercise"_test.py &> /dev/null
        then
            case $exercise in
            "mono") echo -n "mono_test_incorrect|1|" >> test_incorrect_marks;;
            "acronym") echo -n "acronym_test_incorrect|1|" >> test_incorrect_marks;;
            "dateadjust") echo -n "dateadjust_test_incorrect|1|" >> test_incorrect_marks;;
            "questions") echo -n "questions_test_incorrect|2.5|" >> test_incorrect_marks;;
            esac
        fi
    fi
done

git reset --hard HEAD &> /dev/null

touch implementation_marks coverage_marks test_correct_marks test_incorrect_marks
cat implementation_marks coverage_marks test_correct_marks test_incorrect_marks > recorded_marks

echo -e $TXT_RED
echo "Marks awarded"
echo "============="
echo -e $TXT_CLEAR

tr '|' '\n' < recorded_marks | sed -n -e 'N;s/\n/ -> /g;p'
