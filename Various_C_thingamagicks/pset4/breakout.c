//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// paddle size
#define pH 5
#define pW 50

// brick size
#define bH 10
//width is dependent on columns and window width

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// colors for up to 6 rows
string color[] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN", "BLUE"};

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void bounce(int *v);
void startball(int *vx, int *vy);
GLabel initJudgement(GWindow window, int lives);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // starting the ball
    int vx, vy;
    startball(&vx, &vy);
    
    // wait for click before start
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        GEvent event = getNextEvent(ANY_EVENT);
        move(ball, vx, vy);
        GObject object = detectCollision(window, ball);
        if (object != NULL)
        {
            // bounces ball off paddle
            if (object == paddle)
            {
                bounce(&vy);
            }
            // bounces ball off bricks
            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                bricks = bricks - 1;
                // comment bounce out for easy cheat mode :)
                bounce(&vy);
                // awards points according to color
                for (int i = 0; i < ROWS; i++)
                {
                    if (strcmp(getColorGObject(object), color[i]) == 0)
                    {
                        points = points + (ROWS -i);
                    }
                }
                updateScoreboard(window, label, points);
            }
        }
        // window border collisions
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            bounce(&vx);
        }
        else if (getX(ball) <= 0)
        {
            bounce(&vx);
        }
        if (getY(ball) <= 0)
        {
            bounce(&vy);
        }
        // bottom border
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            // takes away your life
            if (lives > 1)
            {
                lives = lives - 1;
                removeGWindow(window, ball);
                ball = initBall(window);
                waitForClick();
                startball(&vx, &vy);
            }
            // game over
            else if (lives == 1)
            {
                break;
            }
        }
        
        if (event != NULL)
        {
            // checks for window closing
            if (getEventType(event) == WINDOW_CLOSED)
            {
                return 0;
            }
            // paddle follows mouse
            else if (getEventType(event) == MOUSE_MOVED)
            {
                setLocation(paddle, (getX(event)-pW/2), getY(paddle));
            }
        }
        pause(10);
    }
    // judges your play
    GLabel Judgment = initJudgement(window, lives);
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/* 
 * starts the ball
 * starting velocity, in pre determined range, 
 * with still varying (varieing?) direction on x axis
 */
void startball(int* vx, int* vy)
{
    *vx = 2 + 1 * drand48();
    *vy = 2 + 1 * drand48();
    if (drand48() < 0.50)
    {
        *vx = - *vx;
    }
}

// bounces the ball
void bounce(int *v)
{
    *v = - *v;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{

    for (int i = 0; i < ROWS; i++)
    {
        
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(j*(WIDTH/COLS), i*bH + 50, WIDTH/COLS - 2, bH - 2);
            setFilled(brick, true);
            setColor(brick, color[i]);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS, 2 * RADIUS, 2 * RADIUS);
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((WIDTH-pW)/2, HEIGHT-20, pW, pH);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-18");
    setLocation(label, (WIDTH - getWidth(label)) / 2, (HEIGHT - getHeight(label)) / 2);
    setColor(label, "LIGHT_GRAY");
    add(window, label);
    return label;
}

/*
 * Signals failure or succes.
 */
GLabel initJudgement(GWindow window, int lives)
{
    if (lives == 1)
    {
        GLabel judgement = newGLabel("you lost... :(");
        setFont(judgement, "SansSerif-18");
        setLocation(judgement, (WIDTH - getWidth(judgement)) / 2, 20 + (HEIGHT - getHeight(judgement)) / 2);
        setColor(judgement, "BLACK");
        add(window, judgement);
        return judgement;
    }
    GLabel judgement = newGLabel("You are winrar! :)");
    setFont(judgement, "SansSerif-18");
    setLocation(judgement, (WIDTH - getWidth(judgement)) / 2, 20 + (HEIGHT - getHeight(judgement)) / 2);
    setColor(judgement, "BLACK");
    add(window, judgement);
    return judgement;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
