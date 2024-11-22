//Developers: Alexis Taggart, Lorenna Solis
//Class: COP2006-80599 Programming 1
//Description: Code in C++ using SFML library to make a music player
//Date: 22 November 2024
//Log
    //October 28, 2024: program created
    //November 1, 2024: SFML successfully integrated using SFML
    //November 5, 2024: Testing SFML, coding started
    //November 6, 2024: Continued coding
    //November 11, 2024: Debugging code, added .dll files into cmake folder
    //November 19, 2024: Added comments and header to code

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
//adding all our libs

sf::Font font;
sf::Text playText, pauseText, stopText, nextText, prevText;
sf::RectangleShape playButton, pauseButton, stopButton, nextButton, prevButton;
sf::Music music;
//initializing all variables for use in code
bool isPlaying = false;
//default for playing music is set to false
size_t currentSongIndex = 0;
//song index set to 0
std::vector<std::string> songs;
//vector made to hold songs

void loadFont()
//first function to load the font
{
    if (!font.loadFromFile("C:/Sour_Gummy/SourGummy-VariableFont_wdth,wght.ttf"))
        //error handling, checking for file using the "not" operator:!
    {
        std::cerr << "Error loading font!" << std::endl;
        //display error message if the font can't load and end program
        exit(1);
    }
    else
    {
        std::cout << "Font loaded successfully." << std::endl;
        //confirms success and moves on
    }
}
void loadButtons()
//function for our buttons
{
    playButton.setSize(sf::Vector2f(150, 50));
    //setting button size
    playButton.setPosition(100, 100);
    //placing button
    playButton.setFillColor(sf::Color::White);
    //setting button color
    playText.setFont(font);
    //using font
    playText.setString("Play");
    //text
    playText.setCharacterSize(24);
    //text size
    playText.setFillColor(sf::Color::Black);
    //text color
    playText.setPosition(130, 115);
    //placing text

    pauseButton.setSize(sf::Vector2f(150, 50));
    pauseButton.setPosition(100, 200);
    pauseButton.setFillColor(sf::Color::White);
    pauseText.setFont(font);
    pauseText.setString("Pause");
    pauseText.setCharacterSize(24);
    pauseText.setFillColor(sf::Color::Black);
    pauseText.setPosition(130, 215);

    stopButton.setSize(sf::Vector2f(150, 50));
    stopButton.setPosition(100, 300);
    stopButton.setFillColor(sf::Color::White);
    stopText.setFont(font);
    stopText.setString("Stop");
    stopText.setCharacterSize(24);
    stopText.setFillColor(sf::Color::Black);
    stopText.setPosition(130, 315);

    nextButton.setSize(sf::Vector2f(150, 50));
    nextButton.setPosition(300, 100);
    nextButton.setFillColor(sf::Color::White);
    nextText.setFont(font);
    nextText.setString("Next");
    nextText.setCharacterSize(24);
    nextText.setFillColor(sf::Color::Black);
    nextText.setPosition(330, 115);

    prevButton.setSize(sf::Vector2f(150, 50));
    prevButton.setPosition(300, 200);
    prevButton.setFillColor(sf::Color::White);
    prevText.setFont(font);
    prevText.setString("Previous");
    prevText.setCharacterSize(24);
    prevText.setFillColor(sf::Color::Black);
    prevText.setPosition(330, 215);
}

void loadSongs()
//load songs
{
    songs.push_back("C:/songs/endofbeginning.wav");
    songs.push_back("C:/songs/midnightcity.wav");
    songs.push_back("C:/songs/dreams.wav");
    //adding songs to vector

    if (!music.openFromFile(songs[currentSongIndex]))
        //check if the song loaded properly
    {
        std::cerr << "Error loading initial song: " << songs[currentSongIndex] << std::endl;
        //error message and exit
        exit(1);
    }

    std::cout << "Playlist loaded, song index: " << currentSongIndex << std::endl;
    //confirm success and move on
}

void playMusic()
//play music
{
    if (!isPlaying)
        //if it's not already playing
    {
        music.play();
        //sfml function to play
        isPlaying = true;
        //is playing is set to true
        std::cout << "Music is now playing." << std::endl;
        //confirm success
    }
}

void pauseMusic()
//function to pause music
{
    if (isPlaying)
        //checks that it is playing
    {
        music.pause();
        //sfml function to pause music
        isPlaying = false;
        //is playing is set to stop
        std::cout << "Music is paused." << std::endl;
        //confirmation message
    }
}

void stopMusic()
//function to stop music
{
    if (isPlaying)
        //checks that it's playing
    {
        music.stop();
        //sfml function to stop (different from pause; this will not resume from where it stopped)
        isPlaying = false;
        //set is playing to false
        std::cout << "Music stopped." << std::endl;
        //confirm
    }
}

void nextSong()
//function to go to next song
{
    currentSongIndex = (currentSongIndex + 1) % songs.size();
    //goes to next song
    if (!music.openFromFile(songs[currentSongIndex]))
        //if it can't load
    {
        std::cerr << "Error loading next song: " << songs[currentSongIndex] << std::endl;
        //error message and exit
        exit(1);
    }
    if (isPlaying)
        //can load and is playing
    {
        music.play();
        //play
    }
    std::cout << "Next song: " << songs[currentSongIndex] << std::endl;
    //confirm
}

void prevSong()
//function for previous song
    {
    currentSongIndex = (currentSongIndex == 0) ? songs.size() - 1 : currentSongIndex - 1;
    //go back in the song list
    if (!music.openFromFile(songs[currentSongIndex]))
        //if it can't load
    {
        std::cerr << "Error loading previous song: " << songs[currentSongIndex] << std::endl;
        //error message and exit
        exit(1);
    }
    if (isPlaying)
        //check is playing bool
    {
        music.play();
        //play music
    }
    std::cout << "Previous song: " << songs[currentSongIndex] << std::endl;
    //confirm
}

int main()
//main!!
{
    sf::RenderWindow window(sf::VideoMode(500, 400), "Music Player");
    //render the window

    loadFont();
    loadButtons();
    loadSongs();
    //load assets using their functions

    std::cout << "Opening window..." << std::endl;
    //confirm

    while (window.isOpen())
        //while it's open
        {
        sf::Event event;
        //checking for events
        while (window.pollEvent(event))
            {
            if (event.type == sf::Event::Closed)
                //if we close it
                {
                window.close();
                std::cout << "Window closed." << std::endl;
                //close the window and display message
            }

            if (event.type == sf::Event::MouseButtonPressed)
                //if button is pressed
                {
                if (event.mouseButton.button == sf::Mouse::Left)
                    //specify left button
                    {
                    if (playButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
                        //this statement fetches the boundaries of the button and is used for all mouse click functions
                    {
                        playMusic();
                    }
                    //call function to play based on where clicked

                    if (pauseButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
                    {
                        pauseMusic();
                    }
                    //call function to pause based on where clicked

                    if (stopButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
                    {
                        stopMusic();
                    }
                    //call function to stop based on where clicked

                    if (nextButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
                    {
                        nextSong();
                    }
                    //call function for next song based on where clicked

                    if (prevButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
                    {
                        prevSong();
                    }
                    //call function for prev song based on where clicked
                }
            }
        }

        window.clear(sf::Color(255, 133, 249));
        //window background color

        window.draw(playButton);
        window.draw(playText);
        window.draw(pauseButton);
        window.draw(pauseText);
        window.draw(stopButton);
        window.draw(stopText);
        window.draw(nextButton);
        window.draw(nextText);
        window.draw(prevButton);
        window.draw(prevText);
        //all of these make the buttons visible

        window.display();
    }

    return 0;
}
