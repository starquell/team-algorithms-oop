#pragma once

#include <cereal/include/cereal/archives/json.hpp>
#include <cereal/include/cereal/types/vector.hpp>
#include <cereal/include/cereal/cereal.hpp>

#include <sstream>
#include <vector>

namespace lab {

    TreeDatabase::TreeDatabase ()
            : _db (_dbPath.data())
    {
        createMainTable();
    }

    TreeDatabase& TreeDatabase::instance () {
        static TreeDatabase db;
        return db;
    }

    template <typename Tree>
    void TreeDatabase::save (const Tree& _tree, std::string_view name) {

        std::vector <typename Tree::value_type> temp (_tree.begin(), _tree.end());
        std::string data;
        {
            std::ostringstream ss;
            cereal::JSONOutputArchive oa(ss);
            oa(temp);
            data = ss.str();
        }
        data += "\n}";

        sqlite3pp::command cmd(_db, "REPLACE INTO main (name, data) VALUES (?, ?)");
        cmd.bind(1, name.data(), sqlite3pp::nocopy);
        cmd.bind(2, data.data(), sqlite3pp::nocopy);

        cmd.execute();
    }

    auto TreeDatabase::loadNames () -> std::vector<std::string> {
        sqlite3pp::query qry (_db, "SELECT name FROM main");

        std::vector<std::string> names;
        names.reserve(std::distance(qry.begin(), qry.end()));

        for (const auto& row : qry) {
            names.emplace_back(std::get<0>(row.get_columns<const char*>(0)));
        }
        return names;
    }

    template <typename Tree>
    auto TreeDatabase::load (std::string_view name) -> std::optional<Tree> {

        const auto cmd = "SELECT data FROM main WHERE name = \""s + name.data() + "\""s;
        sqlite3pp::query qry (_db, cmd.data());

        std::vector <typename Tree::value_type> temp;

        if (std::distance(qry.begin(), qry.end()) == 0) {
            return std::nullopt;
        }
        std::string data = std::get<0>((*qry.begin()).get_columns<const char*>(0));

        {
            std::istringstream ss(data);
            cereal::JSONInputArchive ia (ss);
            ia (temp);
        }

        Tree _tree;
        for (auto& i : temp) {
            _tree.insert(std::move(i));
        }
        return _tree;
    }

    void TreeDatabase::remove (std::string_view name) {
        sqlite3pp::command cmd(_db, "DELETE FROM main WHERE name = (?)");
        cmd.bind(1, name.data(), sqlite3pp::nocopy);
        cmd.execute();
    }

    void TreeDatabase::createMainTable () {
        _db.execute("CREATE TABLE IF NOT EXISTS main ("
                    "name TEXT UNIQUE PRIMARY KEY, "
                    "data TEXT"
                    ")");
    }
}