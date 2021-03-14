// Structure for player settings
struct playerSettings {
    char pChar;
    char pColor;
};

// players can choose their characters.
void choose_char(char *player1_char, char *player2_char);

// players can choose their colors.
void choose_color(char *player1_color, char *player2_color);

// handle settings for the game
void settings(char *player1_char, char *player2_char, char *player1_color, char *player2_color);
