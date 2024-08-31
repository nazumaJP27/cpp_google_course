/* Exercise 2: Final grade calculator.
Here is the grading scheme: 
Final grades will be based on the following:
40% Assignments   15% Midterm Examination
35% Final Examination
10% Class Participation Grade 

Your program should ask the user for the four assignment scores, the midterm, final and section grades.
Then, the final score is calculated and printed.
To do the calculations, you average the four assignment scores together and then multiply it by 0.4 (40%).
You then multiply the midterm score by 0.15, the final by 0.35 and the participation grade by 0.1.
Then you add all the results of these multiplications together.
Example run:
---------------------------------------------
Enter the score for the first assignment. 75
Enter the score for the second assignment. 85
Enter the score for the third assignment. 82
Enter the score for the fourth assignment. 94
Enter the score for the midterm. 81
Enter the score for the final. 89
Enter the score for the section grade. 100
The final grade is: 86.9
---------------------------------------------
Use functions wherever you can in this program.
You can create a function to get the input by passing in as a parameter the string to be displayed in an explanatory cout.
TODO:
Write a program that will compute your final grade for a programming course you are taking. */

#include <iostream>
#include <limits>   // std::numeric_limits
#include <string>
#include <vector>

// Constants
constexpr unsigned int N_ASSIGNMENTS = 4;
constexpr unsigned int N_SCORES = N_ASSIGNMENTS + 3; // '3' stands for the midterm, final, and participation.
constexpr float ASSIGNMENT_WEIGHT = 0.4;
constexpr float MIDTERM_WEIGHT = 0.15;
constexpr float FINAL_WEIGHT = 0.35;
constexpr float PARTICIPATION_WEIGHT = 0.1;

// Enum for score types
enum ScoreType {
    FIRST_ASSIGNMENT,
    SECOND_ASSIGNMENT,
    THIRD_ASSIGNMENT,
    FOURTH_ASSIGNMENT,
    MIDTERM,
    FINAL,
    PARTICIPATION
};

struct Score
{
    std::string name;
    float score;
};

// Prototypes
float final_grade(const std::vector<Score> &scores);
float get_score(const std::string &prompt="Score:");
std::vector<Score> init_scores(void);

int main()
{
    // Initialize a Score vector with all the score types
    std::vector<Score> scores = init_scores();

    // Prompt for scores
    for (int i = 0; i < scores.size(); i++)
    {
        scores[i].score = get_score("Enter the score for the " + scores[i].name);
    }

    // Calculate and print the final grade
    std::cout.precision(1);
    std::cout << std::fixed << "The final grade is: " << final_grade(scores) << std::endl;
    return 0;
}

// Returns a Score vector containing each of the score types 
std::vector<Score> init_scores()
{
    std::vector<Score> scores(N_SCORES);

    scores[FIRST_ASSIGNMENT].name = "first assignment";
    scores[SECOND_ASSIGNMENT].name = "second assignment";
    scores[THIRD_ASSIGNMENT].name = "third assignment";
    scores[FOURTH_ASSIGNMENT].name = "fourth assignment";
    scores[MIDTERM].name = "midterm";
    scores[FINAL].name = "final";
    scores[PARTICIPATION].name = "section grade";

    return scores;
}

// Prompt [custom prompt], validate and return input
float get_score(const std::string &prompt)
{
    float score = -1;
    do
    {
        std::cout << prompt << ": ";
        if (!(std::cin >> score))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input." << std::endl;
            score = -1;
        }
    } while (score < 0);
    return score;
}

// Returns the sum of the scores with their corresponding weights
float final_grade(const std::vector<Score> &scores)
{
    float assignments = 0.0;
    float midterm = scores[MIDTERM].score * MIDTERM_WEIGHT;
    float final = scores[FINAL].score * FINAL_WEIGHT;
    float participation = scores[PARTICIPATION].score * PARTICIPATION_WEIGHT;

    for (int i = 0; i < N_ASSIGNMENTS; i++)
    {
        assignments += (scores[i].score);
    }
    assignments = (assignments / N_ASSIGNMENTS) * ASSIGNMENT_WEIGHT;

    return (assignments + midterm + final + participation);
}