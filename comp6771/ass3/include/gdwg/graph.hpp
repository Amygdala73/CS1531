#ifndef GDWG_GRAPH_HPP
#define GDWG_GRAPH_HPP

#include <iterator>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <set>
#include <map>
#include <typeinfo>
#include <ostream>
#include <initializer_list>
#include <tuple>

namespace gdwg {
	template<typename N, typename E>
	class graph {
	public:
		struct value_type {
			N from;
			N to;
			E weight;
		};

		struct edge {
			N* src;
			N* dst;
			E weight;
		};

		class iterator;

		graph() noexcept = default;

		graph(std::initializer_list<N> il){
			*this = graph(il.begin(), il.end());
		};

		template<typename InputIt>
		graph(InputIt first, InputIt last){
			std::for_each(first, last, [this](N const& n) { insert_node(n); });
		};

		graph(graph&& other) noexcept{
			auto copy = graph(std::move(other));
			copy.swap(*this);
			return *this;
		};

		auto operator=(graph const& other) -> graph& {
			auto copy = graph(std::move(other));
			copy.swap(*this);
			return *this;

		};

		graph(graph const& other) = default;

		auto operator=(graph&& other) noexcept -> graph& {
			if (this == std::addressof(other)) {
				return *this;
			}

			swap(*this, other);
			other.nodes_.clear();
			other.edges_.clear();

			return *this;
		};

		// Modifiers
		auto insert_node(N const& value) -> bool {
			if (!is_node(value)) {
				nodes_.emplace(std::make_shared<N>(value));
				return true;
			}
			return false;
		};

		auto insert_edge(N const& src, N const& dst, E const& weight) -> bool {
			if (not is_node(src) or not is_node(dst)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::insert_edge"
				                         " when either src or dst node does not exist");
			}

			struct edge new_edge = {(*(nodes_.find(src))).get(), (*(nodes_.find(dst))).get(), weight};
			return edges_.emplace(std::make_shared<edge>(new_edge)).second;
		}

		auto replace_node(N const& old_data, N const& new_data) -> bool {
		if (!is_node(old_data)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::replace_node"
				                         " on a node that doesn't exist");
			}
			if (is_node(new_data)) {
				return false;
			}
			auto old_ptr = node_ptr(old_data);
			*old_ptr = new_data;

			return true;
		}

		auto merge_replace_node(N const& old_data, N const& new_data) -> void {
			if (!is_node(old_data) || !is_node(new_data)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::merge_replace_node"
				                         " on old or new data if they don't exist in the graph");
			}
			auto old_ptr = node_ptr(old_data);
			auto new_ptr = node_ptr(new_data);
			auto merge_node = std::vector<std::pair<N*, N*>>();
			for (auto i = edges_.begin(); i != edges_.end(); i++) {
				auto key = i->first;
				if (*key.first == new_data || *key.second == new_data) {
					merge_node.push_back(key);
				}
			}

			for (auto i : merge_node) {
				auto k = edges_.extract(i);
				k.key().second = old_ptr;
				if (k.key().first == new_ptr) {
					k.key().first = old_ptr;
				}
				edges_.insert(std::move(k));
			}

			erase_node(new_data);
			*old_ptr = new_data;
		}

		auto erase_node(N const& value) -> bool {
			if (not is_node(value)) {
				return false;
			}
			std::erase_if(edges_,
			              [&](auto const& e) { return *(e->src) == value or *(e->dst) == value; });
			nodes_.erase(nodes_.find(value));

			return true;
		}

		auto erase_edge(N const& src, N const& dst, E const& weight) -> bool {
		if (!is_node(src) or !is_node(dst)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::erase_edge"
				                         " on src or dst  if they don't exist in the graph");
			}
			return (is_edge(src, dst, weight)
			        and edges_.erase(find_edge(src, dst, weight)));

		}

		auto erase_edge(iterator i) -> iterator {
			auto edge_iter = get_inner(i);
			auto edge_iter_returned = edges_.erase(edge_iter);
			return iterator(edge_iter_returned);
		}

		auto erase_edge(iterator i, iterator s) -> iterator {
			return iterator{edges_.erase(i.iter_, s.iter_)};
		}

		auto clear() noexcept -> void {
			nodes_.clear();
			edges_.clear();
			//weights_.clear();
		}

		// Accessors [gdwg.accessors]
		[[nodiscard]] auto is_node(N const& value) const -> bool {
			return (nodes_.find(value) != std::cend(nodes_));
		}

		[[nodiscard]] auto empty() const -> bool {
			return nodes_.empty();
		}

		[[nodiscard]] auto is_connected(N const& src, N const& dst) const -> bool {

			if (!this->is_node(src) or !this->is_node(dst)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::is_connected if src or dst "
				                         "node don't exist in the graph");
			}

			return std::any_of(edges_.begin(), edges_.end(), [&](auto const& iter) {
				return *(iter->src) == src and *(iter->dst) == dst;
			});
		}

		[[nodiscard]] auto nodes() const -> std::vector<N> {
			auto vec = std::vector<N>();
			for (auto& node : nodes_) {
				vec.push_back(*node.get());
			}
			std::sort(vec.begin(), vec.end());
			return vec;
		}

		[[nodiscard]] auto weights(N const& src, N const& dst) const -> std::vector<E> {
			if (not is_node(src) or not is_node(dst)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::weights if src or dst node "
				                         "don't exist in the graph");
			}
			auto weights = std::vector<E>();
			for (auto const& iter : edges_) {
				if (*(iter->src) == src and *(iter->dst) == dst) {
					weights.push_back(iter->weight);
				}
			}

			return weights;
		}

		[[nodiscard]] auto find(N const& src, N const& dst, E const& weight) const -> iterator {
			return iterator{edges_.find(value_type{src, dst, weight})};
		}

		[[nodiscard]] auto connections(N const& src) const -> std::vector<N> {
			if (!is_node(src)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::connections"
				                         " if src doesn't exist in the graph");
			}
			auto vec = std::set<N>();
			for (auto& [key, value] : edges_) {
				if (*key.first == src) {
					vec.insert(*key.second);
				}
			}
			auto res = std::vector<N>(vec.begin(), vec.end());
			std::sort(res.begin(), res.end());

			return res;
		}

		// Iterator access [gdwg.iterator.access]
		[[nodiscard]] auto begin() const -> iterator {
			return iterator{edges_.begin()};
		}

		[[nodiscard]] auto end() const -> iterator {
			return iterator{edges_.end()};
		}

		// Comparisons [gdwg.cmp]
		[[nodiscard]] auto operator==(graph const& other) const -> bool {
			return static_cast<bool>(this->nodes_() == other.nodes_()
			                         && this->edges_() == other.edges_());
		}

		// Extractor [gdwg.io]
		friend auto operator<<(std::ostream& os, graph const& g) -> std::ostream&{
			auto res = std::ostringstream{};
			std::for_each(g.nodes_.begin(), g.nodes_.end(), [&](auto const& ptr) {
				res << *ptr << " (\n";
				for (auto const& iter : g.edges_) {
					if (*(iter->src) == *ptr) {
						res << "  " << *(iter->dst) << " | " << iter->weight << "\n";
					}
				}
				res << ")\n";
			});
			os << res.str();
			return os;
		};

	private:
		struct node_comparator {
			using is_transparent = void;
			auto operator()(std::shared_ptr<N> const& a,
							std::shared_ptr<N> const& b) const noexcept-> bool {
				return *a < *b;
			}
			auto operator()(std::shared_ptr<N> const& a, N const& b) const noexcept -> bool {
				return *a < b;
			}
			auto operator()(N const& a, std::shared_ptr<N> const& b) const noexcept -> bool {
				return a < *b;
			}
		};


		struct edge_comparator {
			using is_transparent = std::true_type;

			auto operator()(std::shared_ptr<edge> const& a, std::shared_ptr<edge> const& b) const
			   -> bool {
				return std::tie(*(a->src), *(a->dst), a->weight)
				       < std::tie(*(b->src), *(b->dst), b->weight);
			}

			auto operator()(std::shared_ptr<edge> const& a, struct edge const& b) const -> bool {
				return std::tie(*(a->src), *(a->dst), a->weight)
				       < std::tie(*(b.src), *(b.dst), b.weight);
			}

			auto operator()(struct edge const& a, std::shared_ptr<edge> const& b) const -> bool {
				return std::tie(*(a.src), *(a.dst), a.weight)
				       < std::tie(*(b->src), *(b->dst), b->weight);
			}

			auto operator()(std::shared_ptr<edge> const& a, struct value_type const& b) const
			   -> bool {
				return std::tie(*(a->src), *(a->dst), a->weight)
				       < std::tie(b.from, b.to, b.weight);
			}

			auto operator()(struct value_type const& a, std::shared_ptr<edge> const& b) const
			   -> bool {
				return std::tie(a.from, a.to, a.weight)
				       < std::tie(*(b->src), *(b->dst), b->weight);
			}
		};
		/**
		struct weight_comparator {
			using is_transparent = void;
			auto operator()(std::shared_ptr<E> const& a, std::shared_ptr<E> const& b) const noexcept
			   -> bool {
				return *a < *b;
			}
			auto operator()(std::shared_ptr<E> const& a, E const& b) const noexcept -> bool {
				return *a < b;
			}
			auto operator()(E const& a, std::shared_ptr<E> const& b) const noexcept -> bool {
				return a < *b;
			}
		};**/
		std::set<std::shared_ptr<N>, node_comparator> nodes_;
		std::set<std::shared_ptr<edge>, edge_comparator> edges_;
		//std::set<std::shared_ptr<E>, weight_comparator> weights_;

		// Exchange two graphs
		static auto swap(graph<N, E>& first, graph<N, E>& second) noexcept {
			std::swap(first.nodes_, second.nodes_);
			std::swap(first.edges_, second.edges_);
		}

		auto node_ptr(N node) -> N* {
				auto i = [node](auto& j) {
					return node == *j;
				};

				auto res = find_if(nodes_.begin(), nodes_.end(), i);
				if (res == nodes_.end()) {
					return nullptr;
				}
				auto& temp = *res;
				return temp.get();
			}

	//  Iterator [gdwg.iterator]
	public:
		class iterator {
		public:
			using value_type = graph<N, E>::value_type;
			using reference = value_type;
			using pointer = void;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::bidirectional_iterator_tag;
			using inner_iter = typename std::set<std::shared_ptr<edge>, edge_comparator>::iterator;

			inner_iter iter_;

			// Iterator constructor
			iterator() = default;

			// Iterator source
			auto operator*() const -> reference {
				return value_type{*((*iter_)->src), *((*iter_)->dst), (*iter_)->weight};
			}

			// Iterator traversal
			auto operator++() -> iterator& {
				++iter_;
				return *this;
			}

			auto operator++(int) -> iterator {
				auto old = *this;
				++(*this);
				return old;
			}

			auto operator--() -> iterator& {
				--iter_;
				return *this;
			}

			auto operator--(int) -> iterator {
				auto old = *this;
				--(*this);
				return old;
			}

			// Iterator comparison
			auto operator==(iterator const& other) const -> bool {
				return this->iter_ == other.iter_;
			}

		private:
			explicit iterator(inner_iter i): iter_{i} {}
			friend class graph<N, E>;


		};
	};
} // namespace gdwg

#endif // GDWG_GRAPH_HPP