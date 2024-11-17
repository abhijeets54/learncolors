#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <random>
#include <windows.h> // For Windows console colors
#include <iomanip>
#include <conio.h>
#include <algorithm>
#include <ctime>

// Sound effects using Windows Beep (can be replaced with better audio library)
class SoundEffects {
public:
    static void playSuccess() {
        Beep(880, 200);
        Beep(988, 200);
        Beep(1046, 400);
    }

    static void playError() {
        Beep(440, 400);
    }

    static void playWelcome() {
        Beep(523, 200); // C
        Beep(659, 200); // E
        Beep(784, 400); // G
    }
};

// Console color utilities
class ConsoleColor {
public:
    static void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    static void resetColor() {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    static void showRainbow(const std::string& text) {
        const int colors[] = {12, 14, 10, 11, 13, 9}; // Red, Yellow, Green, Cyan, Magenta, Blue
        for (char c : text) {
            for (int color : colors) {
                setColor(color);
                std::cout << c;
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                std::cout << "\b";
            }
            setColor(colors[rand() % 6]);
            std::cout << c;
        }
        resetColor();
        std::cout << std::endl;
    }
};

// Fun animations for kids
class Animations {
public:
    static void showStars() {
        const char* stars[] = {"★ ", "⋆ ", "✦ ", "✭ "};
        for (int i = 0; i < 10; i++) {
            ConsoleColor::setColor(14); // Yellow
            std::cout << stars[i % 4];
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << std::endl;
        ConsoleColor::resetColor();
    }

    static void showCelebration() {
        std::cout << "\n";
        const std::string celebrations[] = {
            "🎈 Wonderful! 🎈", "🌟 Amazing! 🌟", "🎉 Fantastic! 🎉",
            "🌈 Great Job! 🌈", "⭐ Super Star! ⭐", "🏆 You're Amazing! 🏆"
        };
        ConsoleColor::showRainbow(celebrations[rand() % 6]);
    }

    static void loadingAnimation() {
        std::cout << "Loading";
        for (int i = 0; i < 3; i++) {
            std::cout << ".";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        std::cout << "\n";
    }
};

// Rewards and achievement system
class RewardsSystem {
private:
    int stars;
    int totalPoints;
    std::vector<std::string> achievements;
    std::map<std::string, bool> achievementUnlocked;

public:
    RewardsSystem() : stars(0), totalPoints(0) {
        initializeAchievements();
    }

    void addPoints(int points) {
        totalPoints += points;
        int newStars = totalPoints / 100;
        if (newStars > stars) {
            stars = newStars;
            ConsoleColor::setColor(14);
            std::cout << "\n🌟 You earned a new star! 🌟\n";
            ConsoleColor::resetColor();
            SoundEffects::playSuccess();
        }
        checkAchievements();
    }

    void showProgress() {
        std::cout << "\n=== Your Progress ===" << std::endl;

        // Show stars
        ConsoleColor::setColor(14);
        std::cout << "Stars: ";
        for (int i = 0; i < stars; i++) std::cout << "⭐";
        std::cout << " (" << stars << ")" << std::endl;

        // Show points
        ConsoleColor::setColor(11);
        std::cout << "Points: " << totalPoints << std::endl;

        // Show achievements
        if (!achievements.empty()) {
            ConsoleColor::setColor(13);
            std::cout << "\nYour Achievements:" << std::endl;
            for (const auto& achievement : achievements) {
                std::cout << "🏆 " << achievement << std::endl;
            }
        }

        // Show next achievement target
        showNextAchievement();

        ConsoleColor::resetColor();
    }

private:
    void initializeAchievements() {
        achievementUnlocked = {
            {"Color Rookie", false},
            {"Color Explorer", false},
            {"Color Expert", false},
            {"Color Master", false}
        };
    }

    void checkAchievements() {
        if (totalPoints >= 1000 && !achievementUnlocked["Color Master"]) {
            unlockAchievement("Color Master");
        }
        else if (totalPoints >= 500 && !achievementUnlocked["Color Expert"]) {
            unlockAchievement("Color Expert");
        }
        else if (totalPoints >= 200 && !achievementUnlocked["Color Explorer"]) {
            unlockAchievement("Color Explorer");
        }
        else if (totalPoints >= 100 && !achievementUnlocked["Color Rookie"]) {
            unlockAchievement("Color Rookie");
        }
    }

    void unlockAchievement(const std::string& achievement) {
        achievementUnlocked[achievement] = true;
        achievements.push_back(achievement);
        Animations::showCelebration();
        std::cout << "🏆 New Achievement Unlocked: " << achievement << "! 🏆" << std::endl;
        SoundEffects::playSuccess();
    }

    void showNextAchievement() {
        if (!achievementUnlocked["Color Rookie"]) {
            std::cout << "\nNext Achievement: Color Rookie (100 points needed)" << std::endl;
        }
        else if (!achievementUnlocked["Color Explorer"]) {
            std::cout << "\nNext Achievement: Color Explorer (200 points needed)" << std::endl;
        }
        else if (!achievementUnlocked["Color Expert"]) {
            std::cout << "\nNext Achievement: Color Expert (500 points needed)" << std::endl;
        }
        else if (!achievementUnlocked["Color Master"]) {
            std::cout << "\nNext Achievement: Color Master (1000 points needed)" << std::endl;
        }
    }
};

// Mini-games for color learning
class ColorMiniGames {
public:
    static void playColorMixing(const std::string& color1, const std::string& color2) {
        std::cout << "\n=== Color Mixing Game ===" << std::endl;
        std::cout << "What do you get when you mix " << color1 << " and " << color2 << "?" << std::endl;

        std::string result = getColorMixResult(color1, color2);
        std::cout << "Press any key to see the magic!" << std::endl;
        _getch();

        ConsoleColor