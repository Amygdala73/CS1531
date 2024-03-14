#include <q1/q1.hpp>

namespace q1 {


    auto at(const map &mp, int x, int y) -> char {
        return mp[std::size_t(y)][std::size_t(x)];
    }

    auto at(map &mp, int x, int y) -> char& {
        return mp[std::size_t(y)][std::size_t(x)];
    }

    auto make_map(const std::vector<move> & path, const style &styler) -> map {
        (void)path;
        (void)styler;
        /**
        for(auto i:path){
            while(std::next(i,1)!=path.end()){
                styler.style_tile(i,std::next(i,1));
            }
        }**/

        return {{'0'}};
    }

} // namespace q1
