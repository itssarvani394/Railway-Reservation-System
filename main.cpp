#include <iostream>
#include <vector>
#include <map>

class Passenger {
public:
    std::string name;
    int age;
    std::string gender;

    Passenger() : name(""), age(0), gender("") {}
    Passenger(const std::string& passengerName, int passengerAge, const std::string& passengerGender)
        : name(passengerName), age(passengerAge), gender(passengerGender) {}
};

class Train {
public:
    int trainNumber;
    std::string trainName;
    int totalSeats;
    std::vector<Passenger> passengers;

    Train() : trainNumber(0), trainName(""), totalSeats(0) {}
    Train(int number, const std::string& name, int seats)
        : trainNumber(number), trainName(name), totalSeats(seats) {}

    bool isAvailable() {
        return passengers.size() < totalSeats;
    }

    bool reserveSeat(const Passenger& passenger) {
        if (isAvailable()) {
            passengers.push_back(passenger);
            return true;
        }
        return false;
    }

    bool cancelReservation(const Passenger& passenger) {
        for (auto it = passengers.begin(); it != passengers.end(); ++it) {
            if (it->name == passenger.name) {
                passengers.erase(it);
                return true;
            }
        }
        return false;
    }
};

class Day {
public:
    std::string name;
    std::map<int, Train> trains;

    Day() : name("") {}
    Day(const std::string& dayName) : name(dayName) {}

    void addTrain(int trainNumber, const std::string& trainName, int totalSeats) {
        trains.emplace(trainNumber, Train(trainNumber, trainName, totalSeats));
    }
};

class ReservationSystem {
public:
    std::map<std::string, Day> days;

    void addDay(const std::string& dayName) {
        days.emplace(dayName, Day(dayName));
    }

    void displayTrainDetails(const std::string& dayName) {
        if (days.find(dayName) == days.end()) {
            std::cout << "Day not found." << std::endl;
            return;
        }

        Day& day = days[dayName];

        std::cout << "Available Trains for " << day.name << ":" << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << "Train Number\tTrain Name\tTotal Seats\tAvailable Seats" << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;

        for (const auto& pair : day.trains) {
            const Train& train = pair.second;
            std::cout << train.trainNumber << "\t\t" << train.trainName << "\t\t" << train.totalSeats << "\t\t" << train.totalSeats - train.passengers.size() << std::endl;
        }

        std::cout << "-----------------------------------------------------------" << std::endl;
    }

    void displayPassengerDetails(const std::string& dayName, int trainNumber) {
        if (days.find(dayName) == days.end()) {
            std::cout << "Day not found." << std::endl;
            return;
        }

        Day& day = days[dayName];

        if (day.trains.find(trainNumber) == day.trains.end()) {
            std::cout << "Train with number " << trainNumber << " not found." << std::endl;
            return;
        }

        Train& train = day.trains[trainNumber];

        std::cout << "Passenger Details for Train " << train.trainNumber << " (" << train.trainName << ") on " << day.name << ":" << std::endl;
        for (const Passenger& passenger : train.passengers) {
            std::cout << "Passenger Name: " << passenger.name << " (Age: " << passenger.age << ", Gender: " << passenger.gender << ")" << std::endl;
        }
    }

    void bookTicket(const std::string& dayName, int trainNumber, const Passenger& passenger) {
        if (days.find(dayName) == days.end()) {
            std::cout << "Day not found." << std::endl;
            return;
        }

        Day& day = days[dayName];

        if (day.trains.find(trainNumber) == day.trains.end()) {
            std::cout << "Train with number " << trainNumber << " not found." << std::endl;
            return;
        }

        Train& train = day.trains[trainNumber];

        if (train.reserveSeat(passenger)) {
            std::cout << "Successfully reserved a seat in train " << trainNumber << " for " << passenger.name << " on " << day.name << std::endl;
        } else {
            std::cout << "No available seats in train " << trainNumber << " for " << passenger.name << " on " << day.name << std::endl;
        }
    }

    void cancelTicket(const std::string& dayName, int trainNumber, const Passenger& passenger) {
        if (days.find(dayName) == days.end()) {
            std::cout << "Day not found." << std::endl;
            return;
        }

        Day& day = days[dayName];

        if (day.trains.find(trainNumber) == day.trains.end()) {
            std::cout << "Train with number " << trainNumber << " not found." << std::endl;
            return;
        }

        Train& train = day.trains[trainNumber];

        if (train.cancelReservation(passenger)) {
            std::cout << "Successfully canceled reservation for passenger " << passenger.name << " in train " << trainNumber << " on " << day.name << std::endl;
        } else {
            std::cout << "Passenger " << passenger.name << " not found in train " << trainNumber << " on " << day.name << std::endl;
        }
    }
};

int main() {
    ReservationSystem system;

    // Add some sample days and trains
    system.addDay("Monday");
    system.addDay("Tuesday");
    system.addDay("Wednesday");

    system.days["Monday"].addTrain(1, "Express", 100);
    system.days["Monday"].addTrain(2, "Local", 50);
    system.days["Tuesday"].addTrain(3, "Super", 120);

    int choice, age;
    std::string dayName, name, gender;
    int trainNumber;

    do {
        std::cout << "Railway Reservation System Menu:" << std::endl;
        std::cout << "1. Display available trains for a day" << std::endl;
        std::cout << "2. Display passenger details for a train on a day" << std::endl;
        std::cout << "3. Book a ticket" << std::endl;
        std::cout << "4. Cancel a ticket" << std::endl;
        std::cout << "5. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter day name: ";
                std::cin >> dayName;
                system.displayTrainDetails(dayName);
                break;
            case 2:
                std::cout << "Enter day name: ";
                std::cin >> dayName;
                std::cout << "Enter train number: ";
                std::cin >> trainNumber;
                system.displayPassengerDetails(dayName, trainNumber);
                break;
            case 3:
                std::cout << "Enter day name: ";
                std::cin >> dayName;
                std::cout << "Enter train number: ";
                std::cin >> trainNumber;
                std::cout << "Enter passenger name: ";
                std::cin >> name;
                std::cout << "Enter passenger age: ";
                std::cin >> age;
                std::cout << "Enter passenger gender: ";
                std::cin >> gender;
                system.bookTicket(dayName, trainNumber, Passenger(name, age, gender));
                break;
            case 4:
                std::cout << "Enter day name: ";
                std::cin >> dayName;
                std::cout << "Enter train number: ";
                std::cin >> trainNumber;
                std::cout << "Enter passenger name: ";
                std::cin >> name;
                system.cancelTicket(dayName, trainNumber, Passenger(name, 0, ""));
                break;
            case 5:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

    return 0;
}
