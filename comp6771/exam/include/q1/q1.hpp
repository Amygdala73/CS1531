#include <cstddef>
#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>
#include <string>
#include <sstream>
#include <iterator>
#include <functional>
#include <set>
#include <map>
#include <iostream>
#include <ostream>
#include <sstream>

#ifndef Q1_HPP
#define Q1_HPP

namespace q1 {
    using map = std::vector<std::vector<char>>;
    using moves = std::vector<uint8_t>;

    enum class move : uint8_t {
        NN,
        SS,
        WW,
        EE,
        NW,
        NE,
        SW,
        SE,
    };

    class style {
        //friend auto style_tile();
        public:
        style() {
            background_ = ' ';
        }                       // 1
        explicit style(char background){
            background_ = static_cast<char>(background);
        }  // 2
        virtual ~style() noexcept = default;
        // Copy constructor
        // Copy assignment
        // Move constructor
        // Move assignment
        // Member Functions
        auto virtual style_tile() const -> char{
            return background_;
        };
        auto virtual style_tile(move end_move) const -> char{
            (void)end_move;
            //moves.push_back(end_move);
            style('0');
            return background_;
        };
        auto virtual style_tile(move prev_move, move curr_move) const -> char{
            (void)prev_move;
            (void)curr_move;
            //moves.push_back(prev_move);
            //moves.push_back(curr_move);
            style('*');
            return background_;
        };
        private:
        char background_;

    };

    class detailed_style : public style {
        public:
        detailed_style(char end_1, char end_2){
            end_i = static_cast<char>(end_1);
            end_ii = static_cast<char>(end_2);
            background_ = '+';
        };
        // Copy constructor
        // Copy assignment
        // Move constructor
        // Move assignment
        // Member Functions
        auto style_tile(move end_move) const -> char{
            (void)end_move;
            //moves.push_back(end_move);
            //moves.size()>8
            if(counts>8){
                return end_i;
            }
            return end_ii;
        }
        auto style_tile(move prev_move, move curr_move) const -> char{
            (void)prev_move;
            (void)curr_move;
            /*
            if(prev_move!=curr_move){
                if(prev_move == 'NN'|| curr_move == 'NN' ){
                    if(prev_move == 'SS' || curr_move == 'SS' ){
                        style('*');
                    }
                }
            }*/
            return background_;
        }
        private:
        char end_i;
        char end_ii;
        char background_;
        int counts;

    };

    auto at(const map &mp, int x, int y) -> char;
    auto at(map &mp, int x, int y) -> char&;

    auto make_map(const std::vector<move> & path, const style &styler) -> map;

} // namespace q1

#endif // Q1_HPP
