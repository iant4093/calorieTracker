#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <chrono>
#include <sstream>
#include <iomanip>

using namespace std;

class food {
    private:
        string name;
        int calories;
        float protein;
        float carbs;
        float fat;
    public:
        food(string name, int calories, float protein, float carbs, float fat) {
            this->name = name;
            this->calories = calories;
            this->protein = protein;
            this->carbs = carbs;
            this->fat = fat;
        }

        string getName() {
            return name;
        }

        int getCalories() {
            return calories;
        }

        float getProtein() {
            return protein;
        }

        float getCarbs() {
            return carbs;
        }

        float getFat() {
            return fat;
        }

        void setName(string name) {
            this->name = name;
        }

        void setCalories(int calories) {
            this->calories = calories;
        }

        void setProtein(float protein) {
            this->protein = protein;
        }
        
        void setCarbs(float carbs) {
            this->carbs = carbs;
        }

        void setFat(float fat) {
            this->fat = fat;
        }

        bool doesLogExistForDate() {
            ifstream inFile;
            string line;
            
            inFile.open("log.txt");
            
            if (inFile.is_open()) {
                while (getline(inFile, line)) {
                    istringstream iss(line);
                    string key;
                    iss >> key;
                    if (key == "Date:" && line.find(date) != string::npos) {
                        inFile.close();
                        return true;
                    }
                }
                inFile.close();
            }
            return false;
        }

        void deleteLogForDate() {
            ifstream inFile;
            ofstream outFile;
            string line;
            bool found = false;
            
            inFile.open("log.txt");
            outFile.open("temp.txt");

            while (getline(inFile, line)) {
                if (line.find("Date: " + date) != string::npos) {
                    for (int i = 0; i < 5; ++i) {
                        getline(inFile, line); 
                    }
                    found = true;
                } else if (found && line == "") {
                    found = false;
                } else {
                    outFile << line << endl;
                }
            }

            inFile.close();
            outFile.close();
            
            remove("log.txt");
            rename("temp.txt", "log.txt");
        }
        
        void outputLogToFile() {
            if (doesLogExistForDate()) {
                char choice;
                cout << "Log for date " << date << " already exists. Do you want to replace it? (Y/N): ";
                cin >> choice;
                if (toupper(choice) == 'Y') {
                    deleteLogForDate();
                } else {
                    cout << "The log for date " << date << " was not updated.\n";
                    return;
                }
            }
            
            ofstream file;
            file.open("log.txt", ios::app);
            file << "Date: " << date << endl;
            file << "Calories: " << calories << endl;
            file << "Protein: " << protein << endl;
            file << "Carbs: " << carbs << endl;
            file << "Fat: " << fat << endl;
            file << endl;
            file.close();
        }

};

class log {
    private:
        vector<food> foods;
        int calories;
        float protein;
        float carbs;
        float fat;
        string date;
    public:
        log() {
            calories = 0;
            protein = 0;
            carbs = 0;
            fat = 0;
            date = getCurrentDate();
        }

        string getCurrentDate() {
            auto now = chrono::system_clock::now();
            time_t t_now = chrono::system_clock::to_time_t(now);
            tm* date_now = localtime(&t_now);
            ostringstream oss;
            oss << put_time(date_now, "%m/%d/%Y");
            return oss.str();
        }
        
        void addFood(food f) {
            foods.push_back(f);
            calories += f.getCalories();
            protein += f.getProtein();
            carbs += f.getCarbs();
            fat += f.getFat();
        }

        void removeFood(food f) {
            for (int i = 0; i < foods.size(); i++) {
                if (foods[i].getName() == f.getName()) {
                    foods.erase(foods.begin() + i);
                    calories -= f.getCalories();
                    protein -= f.getProtein();
                    carbs -= f.getCarbs();
                    fat -= f.getFat();
                }
            }
        }

        int getCalories() {
            return calories;
        }

        float getProtein() {
            return protein;
        }

        float getCarbs() {
            return carbs;
        }

        float getFat() {
            return fat;
        }

        string getDate() {
            return date;
        }

        void setCalories(int calories) {
            this->calories = calories;
        }

        void setProtein(float protein) {
            this->protein = protein;
        }

        void setCarbs(float carbs) {
            this->carbs = carbs;
        }

        void setFat(float fat) {
            this->fat = fat;
        }

        void setDate(string date) {
            this->date = date;
        }
        
        void outputLogToFile() {
            ofstream file;
            file.open("log.txt", ios::app);
            file << "Date: " << date << endl;
            file << "Calories: " << calories << endl;
            file << "Protein: " << protein << endl;
            file << "Carbs: " << carbs << endl;
            file << "Fat: " << fat << endl;
            file.close();
        }
};

food getFoodFromFoodFile() {
    ifstream file;
    file.open("food.txt");
    string name;
    int calories;
    float protein;
    float carbs;
    float fat;
    file >> name;
    file >> calories;
    file >> protein;
    file >> carbs;
    file >> fat;
    file.close();
    food f(name, calories, protein, carbs, fat);
    return f;
}

log getLogFromLogFile() {
    ifstream file;
    file.open("log.txt");
    string date;
    int calories;
    float protein;
    float carbs;
    float fat;
    file >> date;
    file >> calories;
    file >> protein;
    file >> carbs;
    file >> fat;
    file.close();
    log l;
    l.setDate(date);
    l.setCalories(calories);
    l.setProtein(protein);
    l.setCarbs(carbs);
    l.setFat(fat);
    return l;
}





int main() {

}

