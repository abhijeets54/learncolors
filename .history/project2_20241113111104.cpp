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
        
        ConsoleColor::showRainbow("Mix, mix, mix...");
        std::cout << "You get: " << result << "! ✨" << std::endl;
    }
    
private:
    static std::string getColorMixResult(const std::string& color1, const std::string& color2) {
        if ((color1 == "Red" && color2 == "Blue") || (color1 == "Blue" && color2 == "Red"))
            return "Purple";
        if ((color1 == "Red" && color2 == "Yellow") || (color1 == "Yellow" && color2 == "Red"))
            return "Orange";
        if ((color1 == "Blue" && color2 == "Yellow") || (color1 == "Yellow" && color2 == "Blue"))
            return "Green";
        return "A new color!";
    }
};

// Main color learning system
class ColorLearningSystem {
private:
    struct ColorData {
        std::string name;
        int consoleColor;
        std::string emoji;
        int attempts;
        int successes;
        double difficulty;
        std::chrono::system_clock::time_point lastAttempt;
        std::vector<std::string> funFacts;
        
        ColorData(const std::string& n, int c, const std::string& e, 
                 const std::vector<std::string>& f) : 
            name(n), consoleColor(c), emoji(e), attempts(0), successes(0), 
            difficulty(0.5), funFacts(f) {}
    };
    
    std::vector<ColorData> colors;
    std::map<std::string, size_t> colorIndex;
    RewardsSystem rewards;
    int consecutiveCorrect;

public:
    ColorLearningSystem() : consecutiveCorrect(0) {
        initializeColors();
        showWelcome();
    }
    
    void showWelcome() {
        system("cls");
        SoundEffects::playWelcome();
        ConsoleColor::showRainbow("Welcome to the Magic Color Learning Adventure!");
        std::cout << "\n";
        Animations::showStars();
        
        std::cout << "\n🎨 Let's learn colors together! 🎨" << std::endl;
        std::cout << "\nIn this magical journey, you will:" << std::endl;
        std::cout << "✨ Learn beautiful colors" << std::endl;
        std::cout << "🌟 Earn stars and achievements" << std::endl;
        std::cout << "🎮 Play fun color games" << std::endl;
        std::cout << "📚 Learn interesting color facts" << std::endl;
        
        std::cout << "\nPress any key to start your colorful adventure!" << std::endl;
        _getch();
    }
    
    void presentColor() {
        system("cls");
        size_t index = selectNextColor();
        auto& color = colors[index];
        
        // Show color presentation
        std::cout << "\n=== Magic Color Time! ===" << std::endl;
        ConsoleColor::setColor(color.consoleColor);
        std::cout << "\nLook at this beautiful color!" << std::endl;
        
        // Show color pattern
        for (int i = 0; i < 3; i++) {
            std::cout << color.emoji << " ";
        }
        std::cout << "\n";
        
        // Show random fun fact
        if (!color.funFacts.empty()) {
            std::cout << "\nFun Fact: " 
                     << color.funFacts[rand() % color.funFacts.size()] << std::endl;
        }
        
        std::cout << "\nCan you say this color? It's " << color.name << "!" << std::endl;
        ConsoleColor::resetColor();
        
        // Process response
        processResponse(index);
        
        // Show progress
        rewards.showProgress();
        
        // Maybe play a mini-game
        if (consecutiveCorrect > 0 && consecutiveCorrect % 3 == 0) {
            playRandomMiniGame();
        }
    }
    
    void processResponse(size_t colorIndex) {
        auto& color = colors[colorIndex];
        
        std::cout << "\nDid you say it right? (Y for Yes, N for No)" << std::endl;
        char response = _getch();
        
        color.attempts++;
        color.lastAttempt = std::chrono::system_clock::now();
        
        if (toupper(response) == 'Y') {
            handleCorrectResponse(color);
        } else {
            handleIncorrectResponse(color);
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

private:
    void initializeColors() {
        // Red
        addColor("Red", 12, "🔴", {
            "Red apples are sweet and yummy! 🍎",
            "Fire trucks are bright red! 🚒",
            "Ladybugs are red with black spots! 🐞"
        });
        
        // Blue
        addColor("Blue", 9, "🔵", {
            "The sky is beautiful blue! ☁️",
            "Blueberries are tiny and sweet! 🫐",
            "The ocean is deep blue! 🌊"
        });
        
        // Green
        addColor("Green", 10, "🟢", {
            "Trees have green leaves! 🌳",
            "Frogs are usually green! 🐸",
            "Green means 'Go' on traffic lights! 🚦"
        });
        
        // Yellow
        addColor("Yellow", 14, "🟡", {
            "The sun is bright yellow! ☀️",
            "Bananas are yellow and tasty! 🍌",
            "Baby chicks are yellow and fluffy! 🐥"
        });
        
        // Purple
        addColor("Purple", 13, "🟣", {
            "Grapes can be purple! 🍇",
            "Some butterflies are purple! 🦋",
            "Purple is a royal color! 👑"
        });
        
        // Orange
        addColor("Orange", 6, "🟠", {
            "Oranges are orange! 🍊",
            "Carrots are orange and crunchy! 🥕",
            "The sunset can be orange! 🌅"
        });
    }
    
    void addColor(const std::string& name, int consoleColor, const std::string& emoji,
                 const std::vector<std::string>& funFacts) {
        colorIndex[name] = colors.size();
        colors.emplace_back(name, consoleColor, emoji, funFacts);
    }
    
    size_t selectNextColor() {
        std::vector<double> weights(colors.size());
        auto now = std::chrono::system_clock::now();
        
        for (size_t i = 0; i < colors.size(); i++) {
            auto timeDiff = std::chrono::duration_cast<std::chrono::hours>
                (now - colors[i].lastAttempt).count();
            
            double timeWeight = std::min(1.0, timeDiff / 24.0);
            double successRate = colors[i].attempts > 0 ? 
                static_cast<double>(colors[i].successes) / colors[i].attempts : 0;
            
            weights[i] = (0.4 * colors[i].difficulty) + 
                        (0.3 * timeWeight) + 
                        (0.3 * (1.0 - successRate));
        }
        
std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> dist(weights.begin(), weights.end());
        
        return dist(gen);
    }
    
    void handleCorrectResponse(ColorData& color) {
        color.successes++;
        color.difficulty = std::max(0.0, color.difficulty - 0.1);
        consecutiveCorrect++;
        
        // Celebrate success
        Animations::showCelebration();
        SoundEffects::playSuccess();
        
        // Award points
        int points = 50;
        if (consecutiveCorrect > 1) {
            points += (consecutiveCorrect * 10); // Bonus for streaks
        }
        rewards.addPoints(points);
        
        // Show encouragement
        ConsoleColor::setColor(10); // Green
        std::cout << "\n🌟 You're doing great! Keep going! 🌟" << std::endl;
        if (consecutiveCorrect > 1) {
            std::cout << "Wow! You got " << consecutiveCorrect << " colors right in a row!" << std::endl;
        }
    }
    
    void handleIncorrectResponse(ColorData& color) {
        color.difficulty = std::min(1.0, color.difficulty + 0.15);
        consecutiveCorrect = 0;
        
        // Gentle encouragement
        ConsoleColor::setColor(11); // Cyan
        std::cout << "\n💪 That's okay! Let's try again! 💪" << std::endl;
        std::cout << "Say it with me: " << color.name << "!" << std::endl;
        
        // Show color again with animation
        for (int i = 0; i < 3; i++) {
            std::cout << color.emoji << " ";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        std::cout << std::endl;
        
        rewards.addPoints(10); // Still give some points for trying
    }
    
    void playRandomMiniGame() {
        std::cout << "\n🎮 Bonus Game Time! 🎮" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Randomly select two colors for mixing
        size_t color1Index = rand() % colors.size();
        size_t color2Index = rand() % colors.size();
        while (color2Index == color1Index) {
            color2Index = rand() % colors.size();
        }
        
        ColorMiniGames::playColorMixing(
            colors[color1Index].name,
            colors[color2Index].name
        );
    }
};

// Helper class for memory cleanup and program state
class Program {
private:
    static void setupConsole() {
        // Set console output to support emojis
        SetConsoleOutputCP(CP_UTF8);
        
        // Set console title
        SetConsoleTitleA("Magic Color Learning Adventure!");
        
        // Maximize console window
        ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    }
    
public:
    static void initialize() {
        setupConsole();
        srand(static_cast<unsigned>(time(nullptr)));
    }
    
    static void cleanup() {
        ConsoleColor::resetColor();
        system("cls");
    }
};

int main() {
    try {
        // Initialize program
        Program::initialize();
        
        // Create learning system
        ColorLearningSystem learningSystem;
        
        // Main game loop
        while (true) {
            learningSystem.presentColor();
            
            ConsoleColor::setColor(7); // Reset to default color
            std::cout << "\nWant to learn another color? (Y for Yes, Q to Quit)" << std::endl;
            char input = _getch();
            
            if (toupper(input) == 'Q') {
                break;
            }
        }
        
        // Goodbye message
        system("cls");
        ConsoleColor::showRainbow("Thank you for learning colors with me!");
        std::cout << "\nCome back soon! 👋\n" << std::endl;
        Animations::showStars();
        SoundEffects::playSuccess();
        
        std::cout << "\nPress any key to exit..." << std::endl;
        _getch();
        
        // Cleanup
        Program::cleanup();
        return 0;
    }
    catch (const std::exception& e) {
        ConsoleColor::resetColor();
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        ConsoleColor::resetColor();
        std::cerr << "An unknown error occurred!" << std::endl;
        return 1;
    }
}