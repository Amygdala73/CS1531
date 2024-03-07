import pytest
from collections import defaultdict
from pathlib import Path

class All:
    def __init__(self, needed=0, marks=0):
        self.needed = needed
        self.marks = marks
        self.has = 1

    def __add__(self, other):
        r = All(self.needed, self.marks)
        r.has = self.has + other.has
        return r

    def __str__(self):
        if self.has == self.needed:
            return str(self.marks)
        else:
            return '0'

    def __repr__(self):
        return str(self)

class NoMark:
    def __str__(self):
        return '0'

    def __repr__(self):
        return str(self)

    def __add__(self, other):
        return other

marks_awarded = {}
no_failed_tests = set()

def pytest_configure(config):
    global marks_awarded
    config.addinivalue_line(
        "markers", "marks(value): marks received if test passes"
    )
    marks_awarded = {}
    no_failed_tests = set()

def pytest_addoption(parser):
    parser.addoption("--save-marks", action="store_true")

def pytest_runtest_logreport(report):
    if report.when == 'call':
        file = report.location[0].replace('_test.py', '')
        if report.outcome == "passed":
            props = dict(report.user_properties)
            if 'marks' in props:
                marks_awarded.setdefault(file, NoMark())
                marks = props['marks']
                file = report.location[0].replace('_test.py', '')
                marks_awarded[file] += marks
        elif report.outcome == "failed":
            no_failed_tests.discard(file)

def pytest_collection_modifyitems(session, config, items):
    for item in items:
        if item.config.getoption("--save-marks"):
            for marker in item.iter_markers(name="marks"):
                marks = marker.args[0]
                item.user_properties.append(("marks", marks))
        no_failed_tests.add(Path(item.fspath).name.replace('_test.py', ''))

def pytest_sessionfinish(exitstatus):
    if marks_awarded:
        with open('implementation_marks', 'w') as f:
            for file in marks_awarded:
                f.write(f"{file}_impl|{str(marks_awarded[file])}|")
            print()
        print("Marks recorded: ")
        print(dict(marks_awarded))
    with open('all_passed', 'w', newline="\n") as f:
        f.writelines('\n'.join(no_failed_tests))

