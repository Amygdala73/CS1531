//
//  Copyright UNSW Sydney School of Computer Science and Engineering
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include <comp6771/word_ladder.hpp>

#include <string>
#include <vector>

#include <catch2/catch.hpp>

TEST_CASE("at -> it") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("at", "it", english_lexicon);

	CHECK(std::size(ladders) == 1);
	CHECK(std::is_sorted(ladders.begin(), ladders.end()));
	CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"at", "it"}) == 1);

}

TEST_CASE("ate -> ink") {
	auto const ladders2 = word_ladder::generate("ate", "ink", english_lexicon);

	CHECK(std::size(ladders2) == 3);
	CHECK(std::is_sorted(ladders2.begin(), ladders2.end()));
	CHECK(std::count(ladders2.begin(), ladders2.end(), std::vector<std::string>{"ate", "ink"}) == 0);
}

TEST_CASE("milk -> luck") {
	auto const ladders3 = word_ladder::generate("milk", "luck", english_lexicon);

	CHECK(std::size(ladders3) == 2);
	CHECK(std::is_sorted(ladders3.begin(), ladders3.end()));
	CHECK(std::count(ladders3.begin(), ladders3.end(), std::vector<std::string>{"milk", "luck"}) == 0);

	auto const ladders4 = word_ladder::generate("code", "data", english_lexicon);

	CHECK(std::size(ladders4) == 3);
	CHECK(std::is_sorted(ladders4.begin(), ladders4.end()));
	CHECK(std::count(ladders.begin(),
	                 ladders.end(),
	                 std::vector<std::string>{"code", "cade", "date", "date","data"})
	      == 0);


}

TEST_CASE("airplane -> tricycle") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("airplane", "tricycle", english_lexicon);

	CHECK(std::size(ladders) == 0);
}
//
//  Copyright UNSW Sydney School of Computer Science and Engineering
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include <comp6771/word_ladder.hpp>

#include <string>
#include <vector>

#include <catch2/catch.hpp>

TEST_CASE("at -> it") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("at", "it", english_lexicon);

	CHECK(std::size(ladders) == 1);
	CHECK(std::is_sorted(ladders.begin(), ladders.end()));
	CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"at", "it"}) == 1);

}

TEST_CASE("ate -> ink") {
	auto const ladders2 = word_ladder::generate("ate", "ink", english_lexicon);

	CHECK(std::size(ladders2) == 3);
	CHECK(std::is_sorted(ladders2.begin(), ladders2.end()));
	CHECK(std::count(ladders2.begin(), ladders2.end(), std::vector<std::string>{"ate", "ink"}) == 0);
}

TEST_CASE("milk -> luck") {
	auto const ladders3 = word_ladder::generate("milk", "luck", english_lexicon);

	CHECK(std::size(ladders3) == 2);
	CHECK(std::is_sorted(ladders3.begin(), ladders3.end()));
	CHECK(std::count(ladders3.begin(), ladders3.end(), std::vector<std::string>{"milk", "luck"}) == 0);

	auto const ladders4 = word_ladder::generate("code", "data", english_lexicon);

	CHECK(std::size(ladders4) == 3);
	CHECK(std::is_sorted(ladders4.begin(), ladders4.end()));
	CHECK(std::count(ladders.begin(),
	                 ladders.end(),
	                 std::vector<std::string>{"code", "cade", "date", "date","data"})
	      == 0);


}

TEST_CASE("airplane -> tricycle") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("airplane", "tricycle", english_lexicon);

	CHECK(std::size(ladders) == 0);
}
