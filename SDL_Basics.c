#include "SDL_Basics.h"

void SDL_ExitWithError(const char *string)
{
    SDL_Log("Error : %s > %s\n", string, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void mark(SDL_Renderer *r, int x, int y, int thickness)
{
    for (int a = y - thickness; a <= y + thickness; a++)
        for (int b = x - thickness; b <= x + thickness; b++)
            point(r, b, a);
}

void point(SDL_Renderer *r, int x, int y)
{
    if (SDL_RenderDrawPoint(r, x, y) != 0)
        SDL_ExitWithError("failed to draw point");
}

void line(SDL_Renderer *r, int x1, int y1, int x2, int y2)
{
    if (SDL_RenderDrawLine(r, x1, y1, x2, y2) != 0) // line
        SDL_ExitWithError("failed to draw line");
}

void color(SDL_Renderer *r, int red, int green, int blue, int alpha)
{
    if (SDL_SetRenderDrawColor(r, red, green, blue, alpha) != 0)
        SDL_ExitWithError("failed to set color");
}

void rect(SDL_Renderer *r, int x, int y, int width, int height, int filled)
{
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = width;
    rectangle.h = height;

    if (filled && SDL_RenderFillRect(r, &rectangle) != 0)
            SDL_ExitWithError("failed to draw a full rectangle");
    
    else if (SDL_RenderDrawRect(r, &rectangle) != 0)
            SDL_ExitWithError("failed to draw a full rectangle");
}

void circle(SDL_Renderer *r, int cx, int cy, int radius, int filled)
{
    double precision = 0.5;
    for (int a = cx - radius; a <= cx + radius; a++)
        for (int b = cy - radius; b <= cy + radius; b++)
            if (filled && dist(a, b, cx, cy) <= radius)
                    point(r, a, b);
            else if (dist(a, b, cx, cy) <= radius + precision && dist(a, b, cx, cy) >= radius - precision)
                    point(r, a, b);
}

void openSDL(int x, int y, int mode, const char *name, SDL_Window **w, SDL_Renderer **r)
{

    if (0 != SDL_Init(/*flag*/ SDL_INIT_VIDEO | SDL_INIT_EVENTS)) // lots of flags like SDL_INIT_AUDIO ; *_VIDEO ; *_EVEhTHING... To separe with '|'
        SDL_ExitWithError("Initialisation SDL failed");
    // at this point, the SDL is well initialised, we can afford it because of the if

    *w = SDL_CreateWindow(name, x, y, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    *r = SDL_CreateRenderer(*w, -1, 1);

    if (TTF_Init() != 0)
        SDL_ExitWithError("TTF initialisation failed");
}

void closeSDL(SDL_Window **w, SDL_Renderer **r)
{
    TTF_Quit();
    SDL_DestroyRenderer(*r);
    SDL_DestroyWindow(*w);
    SDL_Quit();
}

void background(SDL_Renderer *r, int red, int green, int blue, int w, int h)
{
    color(r, red, green, blue, 255);
    rect(r, 0, 0, w, h, 1);
}

int rollover(int mx, int my, int x, int y, int w, int h)
{
    if (mx >= x && mx < x + w && my > y && my < y + h)
        return 1; // true
    return 0;     // false
}

int inTheTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double a, double b)
{
    int sign1 = -1, sign2 = -1, sign3 = -1;
    if (((x2 - x1) * (b - y1) - (y2 - y1) * (a - x1)) >= 0)
        sign1 = 1;

    if (((x3 - x2) * (b - y2) - (y3 - y2) * (a - x2)) >= 0)
        sign2 = 1;

    if (((x1 - x3) * (b - y3) - (a - x3) * (y1 - y3)) >= 0)
        sign3 = 1;

    if (sign1 == sign2 && sign2 == sign3)
        return 1;
    return 0;
}

double min(double a, double b, double c)
{
    if (a < b && a < c)
        return a;
    else if (b < a && b < c)
        return b;
    else if (c < a && c < b)
        return c;
}

double max(double a, double b, double c)
{
    if (a > b && a > c)
        return a;
    else if (b > a && b > c)
        return b;
    else if (c > a && c > b)
        return c;
}

void triangle(SDL_Renderer *r, int x1, int y1, int x2, int y2, int x3, int y3, int filled)
{
    line(r, x1, y1, x2, y2);
    line(r, x2, y2, x3, y3);
    line(r, x3, y3, x1, y1);
    
    if(!filled)
        return;

    double s_x = fmin(x1, fmin(x2, x3));
    double s_y = fmin(y1, fmin(y2, y3));
    double f_x = fmax(x1, fmax(x2, x3));
    double f_y = fmax(y1, fmax(y2, y3));
    for (double a = s_x; a <= f_x; a++)
        for (double b = s_y; b <= f_y; b++)
            if (inTheTriangle(x1, y1, x2, y2, x3, y3, a, b))
                point(r, a, b);
        
    

}

void roundRect(SDL_Renderer *r, int x, int y, int width, int height, int filled, int topleft, int topright, int downleft, int downright)
{
    if (topleft <= 0 && topright <= 0 && downleft <= 0 && downright <= 0)
    { // if no curve is needed at all
        if (filled)
        {
            for (int a = x; a <= x + width; a++)
            {
                for (int b = y; b <= y + height; b++)
                {
                    point(r, a, b);
                }
            }
            return;
        }
        else
        {
            line(r, x, y, x + width, y);
            line(r, x, y, x, y + height);
            line(r, x + width, y + height, x + width, y);
            line(r, x + width, y + height, x, y + height);
            return;
        }
    }
    //=================================== modify the rounder of the corner to avoid bugs
    if (topleft + topright >= width)
        topleft = topright = width / 2;
    if (downleft + downright >= width)
        downleft = downright = width / 2;

    if (topright + downright >= height)
        topleft = downright = height / 2;
    if (topleft + downleft >= height)
        topleft = downleft = height / 2;
    double precision = 0.5;

    //====================================
    if (filled == 0)
    {
        line(r, x + topleft, y, x + width - topright, y);                     // top line
        line(r, x + downleft, y + height, x + width - downright, y + height); // bottom line
        line(r, x, y + topleft, x, y + height - downleft);                    // left line
        line(r, x + width, y + topright, x + width, y + height - downright);  // right line

        // top left corner
        for (int a = x; a <= x + topleft; a++)
        {
            for (int b = y; b <= y + topleft; b++)
            {
                if (fabs(dist(a, b, x + topleft, y + topleft) - topleft) <= precision)
                {
                    point(r, a, b);
                }
            }
        }

        // top right corner
        for (int a = x + width - topright; a <= x + width; a++)
        {
            for (int b = y; b <= y + topright; b++)
            {
                if (fabs(dist(a, b, x + width - topright, y + topright) - topright) <= precision)
                {
                    point(r, a, b);
                }
            }
        }

        // bottom right corner
        for (int a = x + width - downright; a <= x + width; a++)
        {
            for (int b = y + height - downright; b <= y + height; b++)
            {
                if (fabs(dist(a, b, x + width - downright, y + height - downright) - downright) <= precision)
                {
                    point(r, a, b);
                }
            }
        }

        // bottom left corner
        for (int a = x; a <= x + downleft; a++)
        {
            for (int b = y + height - downleft; b <= y + height; b++)
            {
                if (fabs(dist(a, b, x + downleft, y + height - downleft) - downleft) <= precision)
                {
                    point(r, a, b);
                }
            }
        }
    }
    else if (filled == 1)
    {

        // top left corner
        for (int a = x; a <= x + topleft; a++)
        {
            for (int b = y; b <= y + topleft; b++)
            {
                if (dist(a, b, x + topleft, y + topleft) <= topleft)
                {
                    point(r, a, b);
                }
            }
        }

        // top right corner
        for (int a = x + width - topright; a <= x + width; a++)
        {
            for (int b = y; b <= y + topright; b++)
            {
                if (dist(a, b, x + width - topright, y + topright) <= topright)
                {
                    point(r, a, b);
                }
            }
        }

        // bottom right corner
        for (int a = x + width - downright; a <= x + width; a++)
        {
            for (int b = y + height - downright; b <= y + height; b++)
            {
                if (dist(a, b, x + width - downright, y + height - downright) <= downright)
                {
                    point(r, a, b);
                }
            }
        }

        // bottom left corner
        for (int a = x; a <= x + downleft; a++)
        {
            for (int b = y + height - downleft; b <= y + height; b++)
            {
                if (dist(a, b, x + downleft, y + height - downleft) <= downleft)
                {
                    point(r, a, b);
                }
            }
        }

        roundRect(r, x + topleft, y,
                  width - topleft - topright, fmax(topleft, topright), 1, 0, 0, 0, 0); // top rect

        roundRect(r, x + downleft, y + height - fmax(downleft, downright),
                  width - downleft - downright, fmax(downleft, downright), 1, 0, 0, 0, 0); // bottom rect

        roundRect(r, x, y + topleft, fmax(topleft, downleft), height - topleft - downleft, 1, 0, 0, 0, 0); // left rect

        roundRect(r, x + width - fmax(topright, downright), y + topright, fmax(topright, downright), height - topright - downright, 1, 0, 0, 0, 0); // right rect

        roundRect(r, x + fmax(topleft, downleft), y + fmax(topleft, topright),
                  width - fmax(downright, topright) - fmax(topleft, downleft), height - fmax(downleft, downright) - fmax(topleft, topright),
                  1, 0, 0, 0, 0); // center rect
    }
}

void setFont(TTF_Font **font, char *font_file, int size)
{
    *font = TTF_OpenFont(font_file, size);
    if (*font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
}

void text(SDL_Renderer *r, int x, int y, char *text, TTF_Font *font, int red, int green, int blue)
{
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Color textColor = {red, green, blue, 0};

    surface = TTF_RenderText_Blended(font, text, textColor);
    texture = SDL_CreateTextureFromSurface(r, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = text_width;
    rectangle.h = text_height;
    SDL_RenderCopy(r, texture, NULL, &rectangle);
    SDL_DestroyTexture(texture);
}

void toChar(char *c, int n)
{
    if (n < 0)
        n = 0;

    c[2] = '0' + (char)(n % 10);
    c[1] = '0' + (char)(n / 10 % 10);
    c[0] = '0' + (char)(n / 100);

    c[3] = '\0';
}

double dist(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void ellipse(SDL_Renderer *r, double x, double y, int w, int h, int filled)
{

    int xc = 0;
    int yc = h;
    long a2 = w * w;
    long b2 = h * h;
    long crit1 = -(a2/4+w % 2 + b2);
    long crit2 = -(b2/4+h % 2 + a2);
    long crit3 = -(b2/4+h % 2);
    long t = -a2 * yc;
    long dxt = 2* b2 * xc;
    long dyt = -2*a2 *yc;
    long d2xt = 2*b2;
    long d2yt = 2*a2;

    while (yc >= 0 && xc <= w)
    {
        if (!filled)
        {
            SDL_RenderDrawPoint(r, x + xc, y + yc);
            SDL_RenderDrawPoint(r, x - xc, y + yc);
            SDL_RenderDrawPoint(r, x + xc, y - yc);
            SDL_RenderDrawPoint(r, x - xc, y - yc);
        }
        else
        {
            line(r, x - xc, y - yc, x + xc, y - yc);
            line(r, x - xc, y + yc, x + xc, y + yc);
        }
        if (t + b2 * xc <= crit1 || /* e(xc+1,yc-1/2) <= 0 */ t + a2 * yc <= crit3)
        { /* e(xc+1/2,yc) <= 0 */
            xc++;
            dxt+= d2xt;
            t += dxt;
        }
        else if (t - a2 * yc > crit2)
        {
            yc--;
            dyt += d2yt;
            t += dyt;
        }
        else
        {
            xc++;
            dxt += d2xt;
            t += dxt;
            yc--;
            dyt +=d2yt;
            t += dyt;
        }
    }
}
