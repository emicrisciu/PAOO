#include <iostream>
#include <string>
// #include <chrono>
// #include <ctime>

class FootballPlayer
{
    private:
        std::string firstName;
        std::string lastName;
        int age;
        std::string position;
        std::string team;
        int goals;

    public:
        FootballPlayer(const std::string& firstName, const std::string& lastName, int age, const std::string& position, const std::string& team)
            : firstName(firstName), lastName(lastName), age(age), position(position), team(team), goals(0)
            {
                std::cout << "The constructor has been invoked" << std::endl;
            }

        FootballPlayer() {}

        std::string getFullName() const
        {
            return firstName + " " + lastName;
        }

        void setFirstName(std::string name){
            firstName = name;
            std::cout <<"First name has been modified!" << std::endl;
        }

        void setLastName(std::string name){
            lastName = name;
            std::cout << "Last name has been modified!" << std::endl;
        }

        int getAge() const
        {
            return age;
        }

        void setAge(int age)
        {
            this->age = age;
            std::cout << "Age has been modified!" << std::endl;
        }

        std::string getPosition() const
        {
            return position;
        }

        void setPosition(std::string position)
        {
            this->position = position;
            std::cout <<"Position has been modified!" << std::endl;
        }

        std::string getTeam() const
        {
            return team;
        }

        void setTeam(std::string team)
        {
            this->team = team;
            std::cout << "Team has been modified!" << std::endl;
        }

        int getGoals() const
        {
            return goals;
        }

        void scoreGoal()
        {
            goals++;
            std::cout << "A goal has been scored!" << std::endl;
        }

        void displayFootballerInfo()
        {
            std::cout << "\n" << "Name: " << getFullName() << "\n"
                << "Age: " << age << "\n"
                << "Position: " << position << "\n"
                << "Team: " << team << "\n"
                << "Goals scored: " << goals << std::endl;
        }

        FootballPlayer operator=(FootballPlayer fp)
        {
            firstName = fp.firstName;
            lastName = fp.lastName;
            age = fp.age;
            position = fp.position;
            team = fp.team;
            return *this;
        }

        ~FootballPlayer()
        {
            std::cout << "Destructor has been called for " << this->getFullName() << std::endl;
        }
};

int main()
{
    FootballPlayer *fp1 = new FootballPlayer("Lionel", "Messi", 37, "CF", "Inter Miami");
    FootballPlayer *fp2 = new FootballPlayer("Cristiano", "Ronaldo", 39, "ST", "Al Nassr");

    fp1->displayFootballerInfo();
    fp2->displayFootballerInfo();

    fp1->setFirstName("Lionel Andres");
    fp1->setAge(25);
    fp1->setTeam("FC Barcelona");
    fp1->setPosition("RW");

    fp2->setAge(27);
    fp2->setTeam("Real Madrid");
    fp2->setPosition("LW");

    fp1->displayFootballerInfo();
    fp2->displayFootballerInfo();

    for(int i = 0; i < 10; i++)
    {
        if(i < 5) fp2->scoreGoal();
        fp1->scoreGoal();
    }

    fp1->displayFootballerInfo();
    fp2->displayFootballerInfo(); 

    fp2 = fp1;

    fp2->displayFootballerInfo();

    delete fp1;
    //delete fp2;

    return 0;
}