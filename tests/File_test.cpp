#include "../include/FileManager.h"
#include "../include/Utils.h"
#include <iostream>

using namespace std;

void printCities(FileManager& dm) {
    cout << "\n=== Cities ===\n";
    for (auto& c : dm.getCities()) {
        cout << c.getId() << " "
             << c.getName() << " ("
             << c.getX() << ","
             << c.getY() << ") "
             << c.getDescription() << "\n";
    }
}

void printEdges(FileManager& dm) {
    cout << "\n=== Edges ===\n";
    for (auto& e : dm.getEdges()) {
        cout << e.getU()
             << " <-> "
             << e.getV() << "\n";
    }
}

int main() {

    cout << "===== Data Layer Test Start =====\n";

    FileManager dm;

    // ---------- Load ----------
    cout << "\n[1] Loading existing data...\n";
    dm.load();
    printCities(dm);
    printEdges(dm);

    // ---------- Add City ----------
    cout << "\n[2] Adding cities...\n";

    dm.addCity(City(1, "Beijing", 10, 20, "Capital"));
    dm.addCity(City(2, "Shanghai", 30, 40, "Finance"));
    dm.addCity(City(3, "Shenzhen", 50, 60, "Tech"));

    // 尝试添加重复城市
    cout << "\n[2.a] Attempting to add duplicates (should be ignored)...\n";
    dm.addCity(City(1, "Beijing", 10, 20, "Capital"));
    dm.addCity(City(2, "Shanghai", 30, 40, "Finance"));

    printCities(dm);

    // ---------- Modify ----------
    cout << "\n[3] Modifying city id=2...\n";

    auto cityOpt = dm.findCity(2);
    if (cityOpt) {
        City* city = cityOpt.value();
        city->setDescription("FinancialCenter");
        city->setPosition(35, 45);
    }

    printCities(dm);

    // demonstrate utility distance calculation
    if (dm.getCities().size() >= 2) {
        auto& c1 = dm.getCities()[0];
        auto& c2 = dm.getCities()[1];
        cout << "\n[3.a] Utility distance between city 0 and 1: "
             << Utils::calculateDistance(c1, c2) << "\n";
    }

    // additional util function demos
    cout << "[3.b] split(\"a,b,c\", ','): ";
    auto parts = Utils::split("a,b,c", ',');
    for (auto &p : parts) cout << p << " ";
    cout << "\n";

    cout << "[3.c] isInteger tests: \"123\" -> " << Utils::isInteger("123")
         << ", \"-45\" -> " << Utils::isInteger("-45")
         << ", \"12a3\" -> " << Utils::isInteger("12a3") << "\n";

    // ---------- Add Edge ----------
    cout << "\n[4] Adding edges...\n";

    dm.addEdge(Edge(1, 2));
    dm.addEdge(Edge(2, 3));

    // 尝试添加重复边
    cout << "\n[4.a] Attempting to add duplicate edges (should be ignored)...\n";
    dm.addEdge(Edge(1, 2));
    dm.addEdge(Edge(3, 2)); // reversed order

    printEdges(dm);

    // ---------- Delete ----------
    cout << "\n[5] Removing city id=3...\n";
    dm.removeCity(3);

    printCities(dm);

    cout << "\n[6] Removing edge 1-2...\n";
    dm.removeEdge(1, 2);

    printEdges(dm);

    // ---------- Save ----------
    cout << "\n[7] Saving to files...\n";
    dm.save();

    // ---------- Reload Verify ----------
    cout << "\n[8] Reloading verification...\n";

    FileManager dm2;
    dm2.load();

    printCities(dm2);
    printEdges(dm2);

    cout << "\n===== TEST FINISHED =====\n";

    return 0;
}