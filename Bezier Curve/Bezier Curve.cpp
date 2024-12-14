#include <glut.h>
#include <glut.h>
#include <vector>
#include <cmath>
#include <string>

struct Button {
    float x, y;           // Position
    float width, height;  // Size
    bool isPressed;
    std::string text;
    bool state;          // Toggle state
};


struct BezierCurve {
    std::vector<GLfloat> points;
    GLfloat lineColor[3];
    GLfloat fillColor[4];  // RGBA for fill color
    GLfloat thickness;
    bool filled;  // Whether this curve should be filled
};

// Global variables
Button toggleButton = {
    -0.9f,              // x
    0.9f,               // y
    0.3f,               // width
    0.1f,               // height
    false,              // isPressed
    "Fill",             // text
    false                // initial state
};

Button controlPointsButton = {
    -0.5f,              // x
    0.9f,               // y
    0.3f,               // width
    0.1f,               // height
    false,              // isPressed
    "Control Points",   // text
    false               // initial state
};



bool showFill = false;
bool showControlPoints = false;
bool mousePressed = false;


std::vector<std::vector<BezierCurve>> curveGroups = {
    // Left Ear Group 
    {
        BezierCurve{
            {

                -0.48f, 0.04f,    
                -0.66f, -0.10f,
                -0.90f, 0.00f,
                -1.04f, 0.50f,
                -0.66f, 1.00f,
                -0.32f, 0.50f,
                -0.40f, 0.24f,


            },
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            3.0f,
            true
        }
    },

    // Right Ear Group 
    {
        BezierCurve{

            {


                0.48f, 0.04f,
                0.66f, -0.10f,
                0.90f, 0.00f,
                1.04f, 0.50f,
                0.66f, 1.00f,
                0.32f, 0.50f,
                0.40f, 0.24f,
            },
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            3.0f,
            true
        }
    },

    // Head/Skull Group 
    {
        BezierCurve{
            {


                -0.40f, 0.24f,
                -0.26f, 0.36f,
                -0.12f, 0.40f,
                 0.00f, 0.40f,
                 0.12f, 0.40f,
                 0.26f, 0.36f,
                 0.40f, 0.24f,

            },
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f, 1.0f},
            3.0f,
            true
        },
    },

    {
        BezierCurve{
            {


                -0.48f, 0.04f,
                -0.52f, -0.12f,
                -0.48f, -0.32f,
                -0.44f, -0.36f,
                -0.36f, -0.44f,
                -0.32f, -0.48f,
                -0.24f, -0.52f,
                -0.16f, -0.54f,
                -0.08f, -0.54f,
                -0.00f, -0.54f,
            },
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f, 1.0f},
            3.0f,
            true
        },
    },

    {
        BezierCurve{
            {
                0.48f, 0.04f,
                0.52f, -0.12f,
                0.48f, -0.32f,
                0.44f, -0.36f,
                0.36f, -0.44f,
                0.32f, -0.48f,
                0.24f, -0.52f,
                0.16f, -0.54f,
                0.08f, -0.54f,
                0.00f, -0.54f,


            },
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f, 1.0f},
            3.0f,
            true
        },
    },

    // Left Cheeks
    {
        BezierCurve{
            {

                -0.32f, -0.20f,
                -0.36f, -0.16f,
                -0.40f, -0.12f,
                -0.52f, -0.12f,
                -0.48f, -0.32f,
                -0.44f, -0.36f,
                -0.36f, -0.44f,
                -0.32f, -0.48f,
                -0.24f, -0.52f,
                -0.16f, -0.54f,
                -0.08f, -0.54f,
                -0.00f, -0.54f,


            },
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f, 1.0f},
            3.0f,
            true
        },
    },

    //Right Cheeks
    {
        BezierCurve{
            {

                0.32f, -0.20f,
                0.36f, -0.16f,
                0.40f, -0.12f,
                0.52f, -0.12f,
                0.48f, -0.32f,
                0.44f, -0.36f,
                0.36f, -0.44f,
                0.32f, -0.48f,
                0.24f, -0.52f,
                0.16f, -0.54f,
                0.08f, -0.54f,
                0.00f, -0.54f,

            },
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f, 1.0f},
            3.0f,
            true
        },
    },

    //Left Face
    {
        BezierCurve{
            {

                -0.32f, -0.20f,
                -0.36f, -0.08f,
                -0.36f, 0.00f,
                -0.36f, 0.10f,
                -0.34f, 0.16f,
                -0.30f, 0.20f,
                -0.26f, 0.26f,
                -0.22f, 0.30f,
                -0.20f, 0.34f,
                -0.16f, 0.36f,
                -0.08f, 0.32f,
                -0.04f, 0.28f,
                -0.00f, 0.20f

            },
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f, 1.0f},
            3.0f,
            true
        },
    },

    //Right Face
    {
        BezierCurve{
            {

                0.32f, -0.20f,
                0.36f, -0.08f,
                0.36f, 0.00f,
                0.36f, 0.10f,
                0.34f, 0.16f,
                0.30f, 0.20f,
                0.26f, 0.26f,
                0.22f, 0.30f,
                0.20f, 0.34f,
                0.16f, 0.36f,
                0.08f, 0.32f,
                0.04f, 0.28f,
                0.00f, 0.20f

            },
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f, 1.0f},
            3.0f,
            true
        },
    },

    // Left Eye
    {
        BezierCurve{
            {

                -0.12f, -0.12f,
                -0.16f, -0.06f,
                -0.16f, 0.04f,
                -0.12f, 0.08f,
                -0.08f, 0.12f,
                -0.04f, 0.08f,
                -0.04f, 0.04f,
                -0.04f, -0.04f,
                -0.06f, -0.10f,
            },
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            2.0f,
            true
        },
    },

    // Right Eye
    {
        BezierCurve{
            {

                0.12f, -0.12f,
                0.16f, -0.06f,
                0.16f, 0.04f,
                0.12f, 0.08f,
                0.08f, 0.12f,
                0.04f, 0.08f,
                0.04f, 0.04f,
                0.04f, -0.04f,
                0.06f, -0.10f,
            },
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            2.0f,
            true
        },
    },
    //Eye Wrinkles
    {
        BezierCurve{
            {

                -0.16f, -0.14f,
                -0.12f, -0.12f,
                 0.00f, -0.04f,
                 0.12f, -0.12f,
                 0.16f, -0.14f,

            },
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f, 1.0f},
            1.0f,
            true
        },
    },
    {
        BezierCurve{
            {

                -0.08f, -0.17f,
                -0.10f, -0.19f,
                -0.10f, -0.21f,
                -0.06f, -0.23f,
                 0.02f, -0.24f,
                 0.10f, -0.23f,
                 0.14f, -0.21f,
                 0.14f, -0.18f,
                 0.12f, -0.17f,
                 0.08f, -0.14f,
                 0.02f, -0.12f,
                -0.04f, -0.14f,
                -0.08f, -0.17f

            },
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            1.0f,
            true
        },
    },
    // Smile Upper    
    {
        BezierCurve{
            {

                -0.34f, -0.24f,
                -0.00f, -0.60f,
                 0.34f, -0.24f,
            },
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            1.0f,
            false
        },
    },
    // Smile lower
    {
        BezierCurve{
            {
                -0.28f, -0.30f,
                -0.00f, -0.76f,
                 0.28f, -0.30f,
            },
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            1.0f,
            false
        },
    },
    //Smile Wrinkles left
    {
        BezierCurve{
            {

                -0.32f, -0.23f,
                -0.35f, -0.22f,
                -0.35f, -0.26f,
            },
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            0.5f,
            false
        },
    },
    //Smile Wrinkles Right
    {
        BezierCurve{
            {

                0.32f, -0.23f,
                0.35f, -0.22f,
                0.35f, -0.26f,
            },
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            0.5f,
            false
        },
    },
    // Left Tongue
    {
        BezierCurve{
            {

                -0.00f, -0.53f,
                -0.08f, -0.51f,
                -0.16f, -0.49f,
                -0.04f, -0.45f,
                -0.00f, -0.48f
            },
            {0.8f, 0.2f, 0.2f},
            {1.0f, 0.0f, 0.0f, 1.0f},
            1.0f,
            true
        },
    },
    // Right Tongue
    {
        BezierCurve{
            {

                0.00f, -0.53f,
                0.08f, -0.51f,
                0.16f, -0.49f,
                0.04f, -0.45f,
                0.00f, -0.48f


            },
            {0.8f, 0.2f, 0.2f},
            {1.0f, 0.0f, 0.0f, 1.0f},
            1.0f,
            true
        },
    },
};



// Modified isInsideButton to work with any button
bool isInsideButton(float x, float y, const Button& btn) {
    return (x >= btn.x && x <= btn.x + btn.width &&
        y >= btn.y - btn.height && y <= btn.y);
}

void screenToOpenGL(int x, int y, float& glX, float& glY) {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Cast to float first and divide before multiplying
    glX = (static_cast<float>(x) / windowWidth) * 2.0f - 1.0f;
    glY = 1.0f - (static_cast<float>(y) / windowHeight) * 2.0f;
}

// Function to draw text
void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

// Function to draw button
void drawButton(const Button& btn) {
    // Draw button background
    glColor3f(btn.state ? 0.7f : 0.5f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(btn.x, btn.y);
    glVertex2f(btn.x + btn.width, btn.y);
    glVertex2f(btn.x + btn.width, btn.y - btn.height);
    glVertex2f(btn.x, btn.y - btn.height);
    glEnd();

    // Draw button border
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(btn.x, btn.y);
    glVertex2f(btn.x + btn.width, btn.y);
    glVertex2f(btn.x + btn.width, btn.y - btn.height);
    glVertex2f(btn.x, btn.y - btn.height);
    glEnd();

    // Draw button text
    glColor3f(0.0f, 0.0f, 0.0f);
    float textX = btn.x + 0.02f;
    float textY = btn.y - btn.height / 2.0f - 0.01f;
    drawText(btn.text.c_str(), textX, textY);
}


// Function to draw control points for a curve
void drawControlPoints(const BezierCurve& curve) {
    glPointSize(5.0f);
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color for control points
    glBegin(GL_POINTS);
    for (size_t i = 0; i < curve.points.size(); i += 2) {
        glVertex2f(curve.points[i], curve.points[i + 1]);
    }
    glEnd();

    // Draw lines connecting control points
    glColor3f(0.5f, 0.5f, 0.5f);  // Gray color for connecting lines
    glLineWidth(1.0f);
    glBegin(GL_LINE_STRIP);
    for (size_t i = 0; i < curve.points.size(); i += 2) {
        glVertex2f(curve.points[i], curve.points[i + 1]);
    }
    glEnd();
}

double nChooseK(int n, int i) {
    if (i == 0 || i == n) return 1;
    if (i > n) return 0;
    
    double result = 1;
    for (int j = 0; j < i; j++) {
        result *= (n - j);
        result /= (j + 1);
    }
    return result;
}

double blendFactor(int n, int i, double t) {
    if (t == 0.0 && i == 0) return 1.0;
    if (t == 1.0 && i == n) return 1.0;
    if (i < 0 || i > n) return 0.0;
    
    return nChooseK(n, i) * pow(1 - t, n - i) * pow(t, i);
}

void calculateBezierPoint(double t, const std::vector<GLfloat>& controls, double& x, double& y) {
    x = y = 0.0;
    int n = (controls.size() / 2) - 1;
    
    for (int i = 0; i <= n; i++) {
        double bern = blendFactor(n, i, t);
        x += controls[i * 2] * bern;
        y += controls[i * 2 + 1] * bern;
    }

}



void fillShape(const std::vector<GLfloat>& points) {
    glBegin(GL_TRIANGLE_FAN);
    // Use the first point as the center point for the triangle fan
    glVertex2f(points[0], points[1]);

    // Add all other points
    for (size_t i = 2; i < points.size(); i += 2) {
        glVertex2f(points[i], points[i + 1]);
    }
    // Close the shape by connecting back to the second point
    glVertex2f(points[2], points[3]);
    glEnd();
}


void drawBezierCurve(const BezierCurve& curve) {
    std::vector<GLfloat> renderPoints;

    // Calculate points for the curve
    for (double t = 0.0; t <= 1.0; t += 0.002) {
        double x, y;
        calculateBezierPoint(t, curve.points, x, y);
        renderPoints.push_back(x);
        renderPoints.push_back(y);
    }

    if (showFill && curve.filled) {
        glColor4fv(curve.fillColor);
        fillShape(renderPoints);
    }

    glColor3fv(curve.lineColor);
    glLineWidth(curve.thickness);
    glBegin(GL_LINE_STRIP);
    for (size_t i = 0; i < renderPoints.size(); i += 2) {
        glVertex2f(renderPoints[i], renderPoints[i + 1]);
    }
    glEnd();

    // Draw control points if enabled
    if (showControlPoints) {
        drawControlPoints(curve);
    }
}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw Mickey Mouse
    for (const auto& group : curveGroups) {
        for (const auto& curve : group) {
            drawBezierCurve(curve);
        }
    }

    drawText("Love Dewangan 500109339", 0.66, -0.98);
    // Draw UI buttons
    drawButton(toggleButton);
    drawButton(controlPointsButton);

    glutSwapBuffers();
}



void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // White background
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}


void mouse(int button, int state, int x, int y) {
    float glX, glY;
    screenToOpenGL(x, y, glX, glY);

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mousePressed = true;
            if (isInsideButton(glX, glY, toggleButton)) {
                toggleButton.isPressed = true;
                toggleButton.state = !toggleButton.state;
                showFill = toggleButton.state;
                glutPostRedisplay();
            }
            else if (isInsideButton(glX, glY, controlPointsButton)) {
                controlPointsButton.isPressed = true;
                controlPointsButton.state = !controlPointsButton.state;
                showControlPoints = controlPointsButton.state;
                glutPostRedisplay();
            }
        }
        else if (state == GLUT_UP) {
            mousePressed = false;
            toggleButton.isPressed = false;
            controlPointsButton.isPressed = false;
        }
    }
}

void motion(int x, int y) {
    if (mousePressed) {
        float glX, glY;
        screenToOpenGL(x, y, glX, glY);

        if (isInsideButton(glX, glY, toggleButton)) {
            if (!toggleButton.isPressed) {
                toggleButton.isPressed = true;
                glutPostRedisplay();
            }
        }
        else if (isInsideButton(glX, glY, controlPointsButton)) {
            if (!controlPointsButton.isPressed) {
                controlPointsButton.isPressed = true;
                glutPostRedisplay();
            }
        }
        else {
            if (toggleButton.isPressed || controlPointsButton.isPressed) {
                toggleButton.isPressed = false;
                controlPointsButton.isPressed = false;
                glutPostRedisplay();
            }
        }
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mickey Mouse");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();
    return 0;
}