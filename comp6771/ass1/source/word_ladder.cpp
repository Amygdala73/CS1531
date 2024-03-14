#include <comp6771/word_ladder.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <queue>
#include <string>
#include <algorithm>
#include <utility>

namespace word_ladder {
	// Construct a sub lexicon that contains all words have same length of the input words
	auto sublexicon(const std::unordered_set<std::string> &lexicon, const size_t &length)
	-> std::unordered_set<std::string>{
		auto sub_lexi = std::unordered_set<std::string>{};
		for (const auto &word : lexicon) {
            if (word.size() == length) {
                sub_lexi.insert(word);
            }
        }
		/**
		for (const auto &word : sub_lexi) {
            std::cout<<word<<std::endl;
        }**/
		//auto sub_sub_lexi = std::unordered_set<std::string>{};
        return sub_lexi;
	}

	// Find whether if a and b differ in only one single character
	auto isAdj(std::string const& strA, std::string const& strB) ->bool{
		/**
		// Having issue with casting int to unsigned int
    	int count = 0;
		int length = int(a.length());
		unsigned u = (length);
    	for (unsigned int i = 0; i <u; ++i) {
        	if (a[i] == b[i])
            	count++;
    	}
    	if (count == 1)
        	return true;
    	return false;
		**/

		auto b = strB.cbegin();

		auto flg = false;

		for (auto a = strA.cbegin(); a != strA.cend();++a) {
			if (flg && *a != *b ) {
				return false;
			}
			if (*a != *b) {
				flg = true;
			}
			++b;
		}

		return true;
	}
	// Bi-directional BFS can have better performance than a single BFS
	/**
	auto bi_BFS(auto const& src, auto const& dest, auto& graph,
	auto& visited, auto const& sub_lexi, std::unordered_set<std::string> lexicon)
	-> std::unordered_map<std::string, std::vector<std::string>>{
		std::string front = src;
		std::string back = dest;
		//Create two queues for two single BFS
	   	auto front_q = std::queue<std::string>{};
		auto back_q = std::queue<std::string>{};
		auto visited_1 = std::unordered_set<std::string>();
		auto visited_2 = std::unordered_set<std::string>();
		auto duplicated = std::unordered_set<std::string>();
		auto found = false;

	   	front_q.push(front);
		back_q.push(back);

		while(!front_q.empty() && !back_q.empty()){
			auto fcurr = front_q.front();
			front_q.pop();

			auto bcurr = back_q.front();
			back_q.pop();

			if(visited_1.size()<visited_2.size()){
				for (auto &word :sub_lexi){
				//std::string iter = *word;
					auto iter = word;

					if(isAdj(fcurr,iter) ){
					// Check if there is any duplicated nodes
						if(count(graph[fcurr].begin(), graph[fcurr].end(), iter)==0){
							graph[fcurr].push_back(iter);
						}

						if(visited.contains(iter)){
							found = true;
						}

						if(!visited.contains(iter)){
							front_q.push(iter);
							visited.insert(iter);
							visited_1.insert(iter);
						}
						if (!duplicated.contains(iter)) {
						duplicated.insert(iter);
						}
					}
				}
			}
			else{
				for (auto &word :sub_lexi){
					auto iter = word;
					if(isAdj(bcurr,iter) ){
						if(count(graph[bcurr].begin(), graph[bcurr].end(), iter)==0){
							graph[bcurr].push_back(iter);
						}

						if(visited.contains(iter)){
							found = true;
						}

						if(!visited.contains(iter)){
							back_q.push(iter);
							visited.insert(iter);
							visited_2.insert(iter);
						}
						if (!duplicated.contains(iter)) {
						duplicated.insert(iter);
						}
					}
				}

			}
		}
		auto dfdf = lexicon;

		for (auto i = duplicated.cbegin(); i != duplicated.cend(); i++) {
			lexicon.erase(lexicon.find(*i));
		}

		return graph;
	}
	**/

	auto graph_gen(std::string const from, std::unordered_set<std::string> sub_lexi,
	std::unordered_map<std::string, std::vector<std::string>> graph)
   -> std::unordered_map<std::string, std::vector<std::string>> {
		auto queue = std::queue<std::string>{};
		auto redundant  = std::unordered_set<std::string>{};

		queue.push(from);
		sub_lexi.erase(from);

		while (!queue.empty()) {
			for (auto i = queue.size(); i > 0; --i) {
				auto current = queue.front();
				queue.pop();
				for (auto& j : sub_lexi) {
					if (isAdj(current, j)) {
						// get neighbours
						graph[current].push_back(j);
						if (!redundant.contains(j)) {
							redundant.insert(j);
							queue.push(j);
						}
					}
				}
			}
			for (auto i : redundant) {
				sub_lexi.erase(i);
			}
			redundant.clear();
		}
		return graph;
	}

	auto single_BFS(std::string const from,
               std::string const to,
               std::unordered_map<std::string, std::vector<std::string>> const graph)
   -> std::vector<std::vector<std::string>> {
		auto paths = std::vector<std::vector<std::string>>{};
		auto queue = std::queue<std::vector<std::string>>{};
		//auto queue2 = std::queue<std::vector<std::string>>{};
		queue.push({from});
		//queue2.push({from});
		//while (!queue.empty()&&!queue2.empty()) {
		while (!queue.empty()) {
			auto path = queue.front();
			//auto path2 = queue2.front();
			for(auto& i:path){
				std::cout<<"path: "<<i<<std::endl;
			}
			/**
			for(auto& i:path2){
				std::cout<<"path2: "<<i<<std::endl;
			}**/

			queue.pop();

			auto const& current = path.back();

			if (current == to) {
				paths.push_back(path);
			}

			if (graph.find(current) != graph.end()) {
				for (auto const& i : graph.find(current)->second) {
					auto branch = std::vector<std::string>(path);
					branch.push_back(i);
					queue.push(branch);
				}
			}
		}
		return paths;
	}

	[[nodiscard]] auto generate(std::string const& from,
	                            std::string const& to,
	                            std::unordered_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>> {
		(void)from;
		(void)to;
		(void)lexicon;

		auto path = std::vector<std::string>{};
		auto paths = std::vector<std::vector<std::string>>{};
		// if two inputs have different lengths or at least one of inputs is not in the lexicon
		if (from.size() != to.size()||!lexicon.contains(from) || !lexicon.contains(to)||from == to) {
			return paths;
		}
		/**
		if (lexicon.contains(from) ) {
			std::cout<< "Inital word in lexicon: " << from << '\n';
		}**/

		//std::cout<< "Inital word: " << from << '\n';
		//std::cout<< "Final word: " << to << '\n';
		//std::cout<<typeid(lexicon).name()<<std::endl;
		//std::cout<<typeid(path).name()<<std::endl;

	    auto const sub_dict = word_ladder::sublexicon(lexicon, from.size());

        //auto graph = std::unordered_map<std::string, std::unordered_set<std::string>>{};
		auto graph = std::unordered_map<std::string, std::vector<std::string>>{};
		//auto visited = std::unordered_set<std::string>();

        //auto found = false;

		//auto const& g = bi_BFS(from, to, graph, visited, sub_dict,lexicon);
		auto const& g =  graph_gen(from, sub_dict, graph);
		/**
		for (auto i: g) {
            std::cout << i.first<< " firsthgh"<<std::endl;
    	}**/
		paths = single_BFS(from, to, g);

		//std::cout << paths.size() << " hsdsdhgh"<<std::endl;

		/**for (auto i: paths) {
        	for (auto j: i)
            	std::cout << j << " hhghgh";
        	std::cout << std::endl;
    	}

		for (auto i: paths) {
        	for (auto j: i)
            	std::cout << j << " hhghssgh";
        	std::cout << std::endl;
    	}**/
		std::sort(paths.begin(), paths.end());
        return paths;

		//path.push_back(from);
		//path.push_back(to);
		//paths.push_back(path);
	}

} // namespace word_ladders