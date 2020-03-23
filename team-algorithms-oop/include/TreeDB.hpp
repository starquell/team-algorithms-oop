#pragma once

#include <AnyTree.hpp>

#include <sqlite3pp/headeronly_src/sqlite3pp.h>
#include <cereal/include/cereal/archives/json.hpp>
#include <cereal/include/cereal/types/vector.hpp>
#include <cereal/include/cereal/cereal.hpp>

#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <optional>

namespace lab {

    using namespace std::string_literals;

    /**
     *  @brief Singleton class represention SQLite-based database for tree (can be any container)
     *
     *   Class operating file with database with filename trees.sqlite located in output binary directory
     */
    class TreeDatabase {
    protected:
        TreeDatabase ();
    public:
        TreeDatabase (const TreeDatabase& other) = delete;
        TreeDatabase& operator= (TreeDatabase other) = delete;

        /**
         *  @return Database instance
         */
        static TreeDatabase& instance();

        /**
         *  @brief Save tree with name to database
         */
        template <typename Tree>
        void save (const Tree& _tree, std::string_view name);

        /**
         *  @return Vector of all trees (theis names) in database
         */
        [[nodiscard]]
        auto loadNames() -> std::vector<std::string>;

        /**
         *  @return Tree with name name and type Tree if success, otherwise - std::nullopt
         */
        template <typename Tree>
        auto load (std::string_view name) -> std::optional<Tree>;

        /**
         *  @brief Remove tree with name name from database;
         */
        void remove (std::string_view name);

    private:

        void createMainTable();

    private:
        constexpr static inline std::string_view _dbPath = "./trees.sqlite";
        sqlite3pp::database _db;
    };
}

#include <TreeDB.tpp>