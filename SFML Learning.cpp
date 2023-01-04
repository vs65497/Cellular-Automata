// Tutorial at: https://youtu.be/VWWSc2nqrEA

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <array>

constexpr int size = 600;
constexpr int max = 200;
constexpr int unit = size / max;

// Create a 2D array to hold the state of each square
std::array<std::array<bool, max>, max> grid;

// Initialize the grid with a random configuration
void initialize()
{
    std::srand(std::time(nullptr));

    int pop = 0.45 * max * max;
    for (int i = 0; i < pop; ++i)
    {
        // Generate random row and column indices
        int row = std::rand() % max;
        int col = std::rand() % max;

        // Set the square at the random indices to true (black)
        grid[row][col] = true;
    }
}

// Update the state of each square based on the rules of the Game of Life
void update()
{
    std::array<std::array<bool, max>, max> update;

    for (int row = 0; row < max; ++row)
    {
        for (int col = 0; col < max; ++col)
        {
            int count = 0;

            // Top Row
            if (row > 0 && col > 0 && grid[row - 1][col - 1]) ++count;
            if (row > 0 && grid[row - 1][col]) ++count;
            if (row > 0 && col < max - 1 && grid[row - 1][col + 1]) ++count;

            // Current Row
            if (col > 0 && grid[row][col - 1]) ++count;
            if (col < max - 1 && grid[row][col + 1]) ++count;

            // Bottom Row
            if (row < max - 1 && col > 0 && grid[row + 1][col - 1]) ++count;
            if (row < max - 1 && grid[row + 1][col]) ++count;
            if (row < max - 1 && col < max - 1 && grid[row + 1][col + 1]) ++count;

            // Live or die
            update[row][col] = (grid[row][col] && (count == 2 || count == 3)) || (!grid[row][col] && count == 3);
        }
    }

    grid = update;
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(size, size), "Game of Life");

    // Set the window's framerate limit
    window.setFramerateLimit(60);

    // Create a white and a black square
    sf::RectangleShape whiteSquare(sf::Vector2f(unit, unit));
    whiteSquare.setFillColor(sf::Color::White);

    sf::RectangleShape blackSquare(sf::Vector2f(unit, unit));
    blackSquare.setFillColor(sf::Color::Black);

    // Initialize the grid
    initialize();

    // Main loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Update the state of the squares
        update();

        // Clear the window
        window.clear();

        // Draw each square on the window
        for (int row = 0; row < max; ++row)
        {
            for (int col = 0; col < max; ++col)
            {
                sf::RectangleShape& square = grid[row][col] ? blackSquare : whiteSquare;
                square.setPosition(row * unit, col * unit);
                window.draw(square);
            }
        }

        // Display the window
        window.display();
    }

    return 0;
}

