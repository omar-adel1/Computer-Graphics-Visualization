#include <QVTKOpenGLNativeWidget.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkLineSource.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPointPicker.h>
#include <vtkCallbackCommand.h>
#include <vtkNamedColors.h>

#include <QApplication>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPointer>
#include <QPushButton>
#include <QVBoxLayout>

#include <cmath>
#include <cstdlib>
#include <random>
#include <qcombobox.h>
#include <vtkLineSource.h>
#include <QFileDialog> 
#include <QInputDialog>
#include <qmessagebox.h>
#include <vtkRegularPolygonSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataWriter.h>
#include <vtkCoordinate.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vtkTextActor.h>
#include <vtkAppendPolyData.h>
#include <vtkConeSource.h>
#include <vtkTextRepresentation.h>
#include <QSpinBox>
#include <QTextEdit>
using namespace std;

vtkNew<vtkRenderer> renderer;

/// Actor, Source, Mapper    FOR  Line
vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> lineSource = vtkSmartPointer<vtkLineSource>::New();
/// Actor, Source, Mapper    FOR  Circle
vtkSmartPointer<vtkActor> actor_circle = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_circle = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> circle_Source = vtkSmartPointer<vtkLineSource>::New();
/// Actor, Source, Mapper    FOR  Ellipse
vtkSmartPointer<vtkActor> actor_Ellipse = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Ellipse = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Ellipse_Source = vtkSmartPointer<vtkLineSource>::New();
/// Actor, Source, Mapper    FOR  Regular Polygon
vtkSmartPointer<vtkActor> actor_Regular_Polygon = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Regular_Polygon = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Regular_Polygon_Source = vtkSmartPointer<vtkLineSource>::New();
/// Actor, Source, Mapper    FOR  Arc
vtkSmartPointer<vtkActor> actor_Arc = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Arc = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Arc_Source = vtkSmartPointer<vtkLineSource>::New();
/// Actor, Source, Mapper    FOR  Cylinder
vtkSmartPointer<vtkActor> actor_Cylinder = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Cylinder = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Cylinder_Source = vtkSmartPointer<vtkLineSource>::New();
/// Actor, Source, Mapper    FOR  Sphere
vtkSmartPointer<vtkActor> actor_Football = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Football = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Football_Source = vtkSmartPointer<vtkLineSource>::New();
/// Actor, Source, Mapper    FOR  Square
vtkSmartPointer<vtkActor> actor_Square = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Square = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Square_Source = vtkSmartPointer<vtkLineSource>::New();
/// Actor, Source, Mapper    FOR  Hexahedron
vtkSmartPointer<vtkActor> actor_Hexahedron = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Hexahedron = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Hexahedron_Source = vtkSmartPointer<vtkLineSource>::New();
/// Actor, Source, Mapper    FOR  Star
vtkSmartPointer<vtkActor> actor_Star = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Star = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Star_Source = vtkSmartPointer<vtkLineSource>::New();

/// Global Initialization
double Radius_Circle;
double Radius_Sphere;
double Radius_Arc;
double Radius_Reg_Polygon;
int NO_POINTS;
double Radius_Cylinder;
double Height_Cylinder;
double MAJOR_AXIS;
double MINOR_AXIS;
double Radius_Hexahedron;
double Radius_Square;
double Radius_Star;
bool Line_Poly;
bool Poly_Line = 0;
double picked[3]; // Declares an array of 3 doubles called "picked"
string mode_line;
double x1_line;
double y1_line;
double x2_line;
double y2_line;
bool is_Polygon = false;
namespace {
    void DrawLine(vtkRenderer* renderer, vtkPoints* points);

    void DrawPoly_Line(vtkRenderer* renderer, vtkPoints* points);

    void Change_Shapes(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window);

    void ChangeColor(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window);

    void UpdateLineThickness(int thickness, vtkGenericOpenGLRenderWindow* window);

    void Save(QComboBox* comboBox);

    void Delete(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window);

    void Transform(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window);

    void Load();
} // namespace

namespace {
    class Node {
    private:
        int item;
        Node* next;
    public:
        void setitem(int x) {
            item = x;
        }
        void setnext(Node* n) {
            next = n;
        }
        int getitem() {
            return item;
        }
        Node* getnext() {
            return next;
        }
    };
    class LinkedList {
    private:
        Node* Head;
    public:

    };
}
namespace {
    class MouseInteractorStylePP : public vtkInteractorStyleTrackballCamera
    {
    private:
        double mousePos[2] = { 0.0, 0.0 };
    public:
        static MouseInteractorStylePP* New();
        int check = 0;
        vtkTypeMacro(MouseInteractorStylePP, vtkInteractorStyleTrackballCamera);
        void setlinesource(vtkSmartPointer<vtkLineSource> lSource) {
            lineSource = lSource;
        }
        void setlineactor(vtkSmartPointer<vtkActor> lactor) {
            actor = lactor;
        }
        vtkSmartPointer<vtkLineSource> getlineSource()
        {
            return lineSource;
        }
        vtkSmartPointer<vtkActor> getLineactor() {
            return actor;
        }
        void SetMousePos(double x, double y)
        {
            mousePos[0] = x;
            mousePos[1] = y;
        }
        double* GetMousePos()
        {
            return mousePos;
        }
        virtual void OnLeftButtonDown() override
        {
            // Get the pixel coordinates of the mouse click event
            double x = this->Interactor->GetEventPosition()[0];
            double y = this->Interactor->GetEventPosition()[1];

            // Set the mouse coordinates
            this->SetMousePos(x, y);

            // Use the vtkPicker to pick an object in the scene at the location of the mouse click event
            this->Interactor->GetPicker()->Pick(
                x, // x-coordinate of the mouse click event
                y, // y-coordinate of the mouse click event
                0, // always zero (z-coordinate of the mouse click event)
                this->Interactor->GetRenderWindow()
                ->GetRenderers()
                ->GetFirstRenderer() // pick from the first renderer in the render window
            );

            // Get the 3D position of the pick location
            this->Interactor->GetPicker()->GetPickPosition(picked);

            // Print the 3D coordinates of the picked location to the console
            std::cout << "Picked value: " << picked[0] << " " << picked[1] << " "
                << picked[2] << std::endl;

            // Increment the check variable to keep track of the number of clicks
            check++;

            // If this is the first click, set the first point and draw a temporary line
            if (Line_Poly == true) {
                if (check == 1) {
                    this->SetFirstPoint();
                    this->SetSecondPoint();
                }
                // If this is the second click, set the second point, draw the final line, and reset the check variable
                else if (check == 2) {
                    this->SetSecondPoint();
                    check = 0;
                }
                this->DrawLine();

            }
            else {
                if (check == 1) {
                    this->SetFirstPoint();
                    this->DrawLine();
                }
                // If this is the second click, set the second point, draw the final line, and reset the check variable
                else if (check == 2) {
                    this->SetSecondPoint();
                    check = 0;
                    this->DrawLine();
                }
            }
            // Forward the left button down event to the parent class vtkInteractorStyleTrackballCamera
            vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
        }
        virtual void SetFirstPoint() {
            lineSource->SetPoint1(picked[0], picked[1], picked[2]); // Set the first endpoint of the line
            return;
        }
        virtual void SetSecondPoint() {
            lineSource->SetPoint2(picked[0], picked[1], picked[2]); // Set the second endpoint of the line
            return;
        }
        virtual void DrawLine()
        {
            // Update the points of the line source
            lineSource->Update();

            // Render the updated line in the renderer
            this->Interactor->GetRenderWindow()
                ->GetRenderers()
                ->GetFirstRenderer()
                ->Render();
        }


    };
    vtkStandardNewMacro(MouseInteractorStylePP);
} // namespace

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // main window
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Computer Graphics & Visualization");
    mainWindow.resize(1200, 900);

    // control area
    QDockWidget controlDock;
    mainWindow.addDockWidget(Qt::LeftDockWidgetArea, &controlDock);

    QLabel controlDockTitle("Control Dock");
    controlDockTitle.setMargin(20);
    controlDock.setTitleBarWidget(&controlDockTitle);
    renderer->SetBackground(0.5, 0.502, 0.5647); // Set the background color of the renderer

    QPointer<QVBoxLayout> dockLayout = new QVBoxLayout();
    QWidget layoutContainer;
    layoutContainer.setLayout(dockLayout);
    controlDock.setWidget(&layoutContainer);

    // Save Button 
    QPushButton saveButton;
    saveButton.setText("Save");
    dockLayout->addWidget(&saveButton);

    // Upload Button 
    QPushButton uploadButton;
    uploadButton.setText("Load");
    dockLayout->addWidget(&uploadButton);

    // Change color Button 
    QPushButton* changeColorButton = new QPushButton("Change color");
    dockLayout->addWidget(changeColorButton);

    // Color droplist
    QComboBox* colorDroplist = new QComboBox();
    colorDroplist->addItem("Red");
    colorDroplist->addItem("Green");
    colorDroplist->addItem("Blue");
    colorDroplist->addItem("Yellow");
    colorDroplist->addItem("Magenta");
    colorDroplist->addItem("Black");
    colorDroplist->addItem("White");
    colorDroplist->setCurrentIndex(0); // Set default value
    dockLayout->addWidget(colorDroplist);

    // Thickness Slider
    QSlider* thicknessSlider = new QSlider(Qt::Horizontal);
    thicknessSlider->setMinimum(1);
    thicknessSlider->setMaximum(20);
    thicknessSlider->setValue(1); // Set default value
    dockLayout->addWidget(thicknessSlider);

    // Chooosing Shapes to draw button
    QPushButton* changeshapes = new QPushButton("Change Shape");
    dockLayout->addWidget(changeshapes);

    // Shapes droplist
    QComboBox* shapesdroplist = new QComboBox();
    shapesdroplist->addItem("Line");
    shapesdroplist->addItem("Polyline");
    shapesdroplist->addItem("Polygon");
    shapesdroplist->addItem("Regular Polygon");
    shapesdroplist->addItem("Circle");
    shapesdroplist->addItem("Arc");
    shapesdroplist->addItem("Ellipse");
    shapesdroplist->addItem("Cylinder");
    shapesdroplist->addItem("Hexahedron");
    shapesdroplist->addItem("Sphere");
    shapesdroplist->addItem("Square");
    shapesdroplist->addItem("Star");
    shapesdroplist->setCurrentIndex(0); // Set default value
    dockLayout->addWidget(shapesdroplist);

    // Delete button
    QPushButton* delete_button = new QPushButton("Delete");
    dockLayout->addWidget(delete_button);

    // Change color Button 
    QPushButton* trasform_button = new QPushButton("Transform");
    dockLayout->addWidget(trasform_button);

    // Trnsform droplist
    QComboBox* transform_list = new QComboBox();
    transform_list->addItem("Translation");
    transform_list->addItem("Scaling");
    transform_list->addItem("Rotating");
    transform_list->addItem("Shearing");
    transform_list->setCurrentIndex(0); // Set default value
    dockLayout->addWidget(transform_list);

    // Create a QLineEdit object for the input text field
    QLineEdit* inputTextField_X = new QLineEdit();
    inputTextField_X->setPlaceholderText("Enter X");
    dockLayout->addWidget(inputTextField_X);

    // Create a QLineEdit object for the input text field
    QLineEdit* inputTextField_Y = new QLineEdit();
    inputTextField_Y->setPlaceholderText("Enter Y");
    dockLayout->addWidget(inputTextField_Y);

    // Add Point button
    QPushButton* add_point = new QPushButton("Add Point");
    dockLayout->addWidget(add_point);

    // render area
    QPointer<QVTKOpenGLNativeWidget> vtkRenderWidget =
        new QVTKOpenGLNativeWidget();
    mainWindow.setCentralWidget(vtkRenderWidget);

    // VTK part
    vtkNew<vtkGenericOpenGLRenderWindow> window;
    vtkRenderWidget->setRenderWindow(window.Get());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetEdgeVisibility(true);
    actor->GetProperty()->SetRepresentationToSurface();

    renderer->AddActor(actor);

    window->AddRenderer(renderer);

    // Use a lambda function with capture by reference
    QObject::connect(changeshapes, &QPushButton::clicked,
        [=, &shapesdroplist, &window]() { Change_Shapes(shapesdroplist, window); });

    // Connect Change Color 
    QObject::connect(changeColorButton, &QPushButton::clicked,
        [=, &colorDroplist, &window]() { ChangeColor(colorDroplist, window); });

    // Connect Change Thickness
    QObject::connect(thicknessSlider, &QSlider::valueChanged, [&]() {
        int thickness = thicknessSlider->value();
        UpdateLineThickness(thickness, window);
        });

    // Connect save button
    QObject::connect(&saveButton, &QPushButton::released,
        [&]() {  ::Save(shapesdroplist); });

    // Connect upload button
    QObject::connect(&uploadButton, &QPushButton::released,
        [&]() {  ::Load(); });


    // Connect Delete Button
    QObject::connect(delete_button, &QPushButton::clicked,
        [=, &shapesdroplist, &window]() { Delete(shapesdroplist, window); });

    // Connect Change Color 
    QObject::connect(trasform_button, &QPushButton::clicked,
        [=, &transform_list, &window]() { Transform(transform_list, window); });

    mainWindow.show();

    return app.exec();
}

namespace {
    void Draw_circle(double radius, string color, int thickness)
    {
        double R = radius; // Radius of the circle
        int numPoints = 100; // Number of points to approximate the circle

        lineSource->SetResolution(numPoints);
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Generate points on the circle using parametric equations
        for (int i = 0; i <= numPoints; i++)
        {
            double t = static_cast<double>(i) / numPoints;
            double x = R * cos(2 * vtkMath::Pi() * t);
            double y = R * sin(2 * vtkMath::Pi() * t);
            points->InsertNextPoint(x, y, 0.0); // Insert points on the circle
        }
        circle_Source->SetPoints(points);

        // Update the mapper with the new data
        mapper_circle->SetInputConnection(circle_Source->GetOutputPort());
        mapper_circle->Update();

        // Update the actor with the new mapper and properties based on user's choice
        actor_circle->SetMapper(mapper_circle);
        if (color == "Red") {
            actor_circle->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color == "Blue") {
            actor_circle->GetProperty()->SetColor(0.0, 0.0, 1.0);
        }
        else if (color == "Yellow") {
            actor_circle->GetProperty()->SetColor(1.0, 1.0, 0.0);
        }
        else if (color == "Green") {
            actor_circle->GetProperty()->SetColor(0.0, 1.0, 0.0);
        }
        else if (color == "Magenta") {
            actor_circle->GetProperty()->SetColor(1.0, 0.0, 1.0);
        }
        else if (color == "Black") {
            actor_circle->GetProperty()->SetColor(0.0, 0.0, 0.0);
        }
        else if (color == "White") {
            actor_circle->GetProperty()->SetColor(1.0, 1.0, 1.0);
        }
        actor_circle->GetProperty()->SetLineWidth(thickness);

        // Add the actor to the renderer
        renderer->AddActor(actor_circle);
    }

    void Draw_Ellipse(double x_axis, double y_axis, string color, int thickness) {
        // Create an ellipse using parametric equations
        double A = x_axis; // Major axis length
        double B = y_axis; // Minor axis length
        int numPoints = 100; // Number of points to approximate the ellipse

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        for (int i = 0; i <= numPoints; ++i) // Include the last point to complete the ellipse
        {
            double t = 2 * vtkMath::Pi() * static_cast<double>(i) / numPoints;
            double x = A * cos(t);
            double y = B * sin(t);
            points->InsertNextPoint(x, y, 0.0);
        }

        Ellipse_Source->SetPoints(points);

        mapper_Ellipse->SetInputConnection(Ellipse_Source->GetOutputPort());

        actor_Ellipse->SetMapper(mapper_Ellipse);
        if (color == "Red") {
            actor_Ellipse->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color == "Blue") {
            actor_Ellipse->GetProperty()->SetColor(0.0, 0.0, 1.0);
        }
        else if (color == "Yellow") {
            actor_Ellipse->GetProperty()->SetColor(1.0, 1.0, 0.0);
        }
        else if (color == "Green") {
            actor_Ellipse->GetProperty()->SetColor(0.0, 1.0, 0.0);
        }
        else if (color == "Magenta") {
            actor_Ellipse->GetProperty()->SetColor(1.0, 0.0, 1.0);
        }
        else if (color == "Black") {
            actor_Ellipse->GetProperty()->SetColor(0.0, 0.0, 0.0);
        }
        else if (color == "White") {
            actor_Ellipse->GetProperty()->SetColor(1.0, 1.0, 1.0);
        }
        actor_Ellipse->GetProperty()->SetLineWidth(thickness);

        // Add the actor to the renderer
        renderer->AddActor(actor_Ellipse);

    }

    void Draw_Regular_Polygon(double radius, int no_points, string color, int thickness) {
        // Define parameters for the regular polygon
        double R = radius; // Radius of the regular polygon
        int numPoints = no_points; // Number of points to approximate the regular polygon
        double angleIncrement = 2 * vtkMath::Pi() / numPoints; // Angle increment between consecutive points

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Generate points on the regular polygon using parametric equation
        for (int i = 0; i <= numPoints; i++)
        {
            double angle = i * angleIncrement;
            double x = R * cos(angle);
            double y = R * sin(angle);
            points->InsertNextPoint(x, y, 0.0); // Insert points on the regular polygon
        }

        // Set the points as the input points for the line source
        Regular_Polygon_Source->SetPoints(points);

        // Update the mapper with the line source output
        mapper_Regular_Polygon->SetInputConnection(Regular_Polygon_Source->GetOutputPort());

        // Update the actor with the mapper and properties
        actor_Regular_Polygon->SetMapper(mapper_Regular_Polygon);
        if (color == "Red") {
            actor_Regular_Polygon->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color == "Blue") {
            actor_Regular_Polygon->GetProperty()->SetColor(0.0, 0.0, 1.0);
        }
        else if (color == "Yellow") {
            actor_Regular_Polygon->GetProperty()->SetColor(1.0, 1.0, 0.0);
        }
        else if (color == "Green") {
            actor_Regular_Polygon->GetProperty()->SetColor(0.0, 1.0, 0.0);
        }
        else if (color == "Magenta") {
            actor_Regular_Polygon->GetProperty()->SetColor(1.0, 0.0, 1.0);
        }
        else if (color == "Black") {
            actor_Regular_Polygon->GetProperty()->SetColor(0.0, 0.0, 0.0);
        }
        else if (color == "White") {
            actor_Regular_Polygon->GetProperty()->SetColor(1.0, 1.0, 1.0);
        }
        actor_Regular_Polygon->GetProperty()->SetLineWidth(thickness);

        // Add the actor to the renderer
        renderer->AddActor(actor_Regular_Polygon);
    }

    void Draw_Arc(double radius, string color, int thickness) {
        // Define parameters for the arc
        double R = radius; // Radius of the arc
        double startAngle = 1.0; // Start angle of the arc in radians
        double endAngle = vtkMath::Pi(); // End angle of the arc in radians
        int numPoints = 100; // Number of points to approximate the arc

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Generate points on the arc using parametric equation
        double angleIncrement = (endAngle - startAngle) / numPoints;
        for (int i = 0; i <= numPoints; i++)
        {
            double angle = startAngle + i * angleIncrement;
            double x = R * cos(angle);
            double y = R * sin(angle);
            points->InsertNextPoint(x, y, 0.0); // Insert points on the arc
        }

        // Set the points as the input points for the line source
        Arc_Source->SetPoints(points);

        // Update the mapper with the line source output
        mapper_Arc->SetInputConnection(Arc_Source->GetOutputPort());

        // Update the actor with the mapper and properties
        actor_Arc->SetMapper(mapper_Arc);
        if (color == "Red") {
            actor_Arc->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color == "Blue") {
            actor_Arc->GetProperty()->SetColor(0.0, 0.0, 1.0);
        }
        else if (color == "Yellow") {
            actor_Arc->GetProperty()->SetColor(1.0, 1.0, 0.0);
        }
        else if (color == "Green") {
            actor_Arc->GetProperty()->SetColor(0.0, 1.0, 0.0);
        }
        else if (color == "Magenta") {
            actor_Arc->GetProperty()->SetColor(1.0, 0.0, 1.0);
        }
        else if (color == "Black") {
            actor_Arc->GetProperty()->SetColor(0.0, 0.0, 0.0);
        }
        else if (color == "White") {
            actor_Arc->GetProperty()->SetColor(1.0, 1.0, 1.0);
        }
        actor_Arc->GetProperty()->SetLineWidth(thickness);

        // Add the actor to the renderer
        renderer->AddActor(actor_Arc);

    }

    void Draw_Cylinder(double radius, double height, string color, int thickness) {
        // Define parameters for the cylinder
        double R = radius; // Radius of the cylinder
        double H = height; // Height of the cylinder
        int numPoints = 1000; // Number of points to approximate the cylinder

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Generate points on the cylinder using parametric equation
        double angleIncrement = 2 * vtkMath::Pi() / numPoints;
        for (int i = 0; i <= numPoints; i++)
        {
            double angle = i * angleIncrement;
            double x = R * cos(angle);
            double y = R * sin(angle);
            double z = (i % 2 == 0) ? H / 2.0 : -H / 2.0; // Alternate between positive and negative z values to create the top and bottom faces of the cylinder
            points->InsertNextPoint(x, y, z); // Insert points on the cylinder
        }

        // Set the points as the input points for the line source
        Cylinder_Source->SetPoints(points);

        // Update the mapper with the line source output
        mapper_Cylinder->SetInputConnection(Cylinder_Source->GetOutputPort());

        // Update the actor with the mapper and properties
        actor_Cylinder->SetMapper(mapper_Cylinder);
        if (color == "Red") {
            actor_Cylinder->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color == "Blue") {
            actor_Cylinder->GetProperty()->SetColor(0.0, 0.0, 1.0);
        }
        else if (color == "Yellow") {
            actor_Cylinder->GetProperty()->SetColor(1.0, 1.0, 0.0);
        }
        else if (color == "Green") {
            actor_Cylinder->GetProperty()->SetColor(0.0, 1.0, 0.0);
        }
        else if (color == "Magenta") {
            actor_Cylinder->GetProperty()->SetColor(1.0, 0.0, 1.0);
        }
        else if (color == "Black") {
            actor_Cylinder->GetProperty()->SetColor(0.0, 0.0, 0.0);
        }
        else if (color == "White") {
            actor_Cylinder->GetProperty()->SetColor(1.0, 1.0, 1.0);
        }
        actor_Cylinder->GetProperty()->SetLineWidth(thickness);

        // Add the actor to the renderer
        renderer->AddActor(actor_Cylinder);

    }

    void Draw_Football(double radius, string color, int thickness) {
        // Define parameters for the sphere
        double R = radius; // Radius of the sphere
        int numPointsTheta = 100; // Number of points in theta direction
        int numPointsPhi = 50; // Number of points in phi direction

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Generate points on the sphere using parametric equation
        double thetaIncrement = vtkMath::Pi() / numPointsTheta;
        double phiIncrement = 2 * vtkMath::Pi() / numPointsPhi;
        for (int i = 0; i <= numPointsTheta; i++)
        {
            double theta = i * thetaIncrement;
            for (int j = 0; j <= numPointsPhi; j++)
            {
                double phi = j * phiIncrement;
                double x = R * sin(theta) * cos(phi);
                double y = R * sin(theta) * sin(phi);
                double z = R * cos(theta);
                points->InsertNextPoint(x, y, z); // Insert points on the sphere
            }
        }

        // Set the points as the input points for the line source
        Football_Source->SetPoints(points);

        // Update the mapper with the line source output
        mapper_Football->SetInputConnection(Football_Source->GetOutputPort());

        // Update the actor with the mapper and properties
        actor_Football->SetMapper(mapper_Football);
        if (color == "Red") {
            actor_Football->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color == "Blue") {
            actor_Football->GetProperty()->SetColor(0.0, 0.0, 1.0);
        }
        else if (color == "Yellow") {
            actor_Football->GetProperty()->SetColor(1.0, 1.0, 0.0);
        }
        else if (color == "Green") {
            actor_Football->GetProperty()->SetColor(0.0, 1.0, 0.0);
        }
        else if (color == "Magenta") {
            actor_Football->GetProperty()->SetColor(1.0, 0.0, 1.0);
        }
        else if (color == "Black") {
            actor_Football->GetProperty()->SetColor(0.0, 0.0, 0.0);
        }
        else if (color == "White") {
            actor_Football->GetProperty()->SetColor(1.0, 1.0, 1.0);
        }
        actor_Football->GetProperty()->SetLineWidth(thickness);

        // Add the actor to the renderer
        renderer->AddActor(actor_Football);

    }

    void Draw_Square(double radius_square, string color, int thickness)
    {
        // Define the center point of the hexahedron
        double center[3] = { 0.0, 0.0, 0.0 };

        // Define the radius from the center to each vertex
        double radius = radius_square;

        // Calculate the coordinates of the vertices of the upper part of the hexahedron
        double upperVertices[5][3] = { {center[0] - radius, center[1] - radius, 0},
                                       {center[0] - radius, center[1] + radius, 0},
                                       {center[0] + radius, center[1] + radius, 0},
                                       {center[0] + radius, center[1] - radius, 0},
                                       {center[0] - radius, center[1] - radius, 0} };

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Insert the vertices of the upper part of the hexahedron as points in the points array
        for (int i = 0; i < 5; i++)
        {
            points->InsertNextPoint(upperVertices[i]);
        }

        // Set the points and cells as the input data for the line source
        Square_Source->SetPoints(points);
        //lineSource->SetCells(VTK_HEXAHEDRON, hexahedronCells);

        // Update the mapper with the line source output
        mapper_Square->SetInputConnection(Square_Source->GetOutputPort());

        // Update the actor with the mapper and properties

        actor_Square->SetMapper(mapper_Square);
        if (color == "Red") {
            actor_Square->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color == "Blue") {
            actor_Square->GetProperty()->SetColor(0.0, 0.0, 1.0);
        }
        else if (color == "Yellow") {
            actor_Square->GetProperty()->SetColor(1.0, 1.0, 0.0);
        }
        else if (color == "Green") {
            actor_Square->GetProperty()->SetColor(0.0, 1.0, 0.0);
        }
        else if (color == "Magenta") {
            actor_Square->GetProperty()->SetColor(1.0, 0.0, 1.0);
        }
        else if (color == "Black") {
            actor_Square->GetProperty()->SetColor(0.0, 0.0, 0.0);
        }
        else if (color == "White") {
            actor_Square->GetProperty()->SetColor(1.0, 1.0, 1.0);
        }
        actor_Square->GetProperty()->SetLineWidth(thickness);
        // Add the actor to the renderer
        renderer->AddActor(actor_Square);
    }

    void Draw_Hexahedron(double radius_hex, string color, int thickness)
    {
        // Define the center point of the hexahedron
        double center[3] = { 0.0, 0.0, 0.0 };

        // Define the radius from the center to each vertex
        double radius = radius_hex;

        // Calculate the coordinates of the vertices of the upper part of the hexahedron
        double upperVertices[5][3] = { {center[0] - radius, center[1] - radius, center[2] + radius},
                                       {center[0] - radius, center[1] + radius, center[2] + radius},
                                       {center[0] + radius, center[1] + radius, center[2] + radius},
                                       {center[0] + radius, center[1] - radius, center[2] + radius},
                                       {center[0] - radius, center[1] - radius, center[2] + radius} };

        // Define the coordinates of the vertices of the lower part of the hexahedron
        double lowerVertices[5][3] = { {center[0] - radius, center[1] - radius, center[2] - radius},
                                       {center[0] - radius, center[1] + radius, center[2] - radius},
                                       {center[0] + radius, center[1] + radius, center[2] - radius},
                                       {center[0] + radius, center[1] - radius, center[2] - radius},
                                       {center[0] - radius, center[1] - radius, center[2] - radius} };

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Insert the vertices of the upper part of the hexahedron as points in the points array
        for (int i = 0; i < 5; i++)
        {
            points->InsertNextPoint(upperVertices[i]);
        }

        // Insert the vertices of the lower part of the hexahedron as points in the points array
        for (int i = 0; i < 5; i++)
        {
            points->InsertNextPoint(lowerVertices[i]);
        }

        points->InsertNextPoint(upperVertices[1]);
        points->InsertNextPoint(lowerVertices[1]);
        points->InsertNextPoint(lowerVertices[2]);
        points->InsertNextPoint(upperVertices[2]);
        points->InsertNextPoint(upperVertices[3]);
        points->InsertNextPoint(lowerVertices[3]);
        points->InsertNextPoint(lowerVertices[4]);
        points->InsertNextPoint(upperVertices[4]);

        // Set the points and cells as the input data for the line source
        Hexahedron_Source->SetPoints(points);
        //lineSource->SetCells(VTK_HEXAHEDRON, hexahedronCells);

        // Update the mapper with the line source output
        mapper_Hexahedron->SetInputConnection(Hexahedron_Source->GetOutputPort());

        // Update the actor with the mapper and properties

        actor_Hexahedron->SetMapper(mapper_Hexahedron);
        if (color == "Red") {
            actor_Hexahedron->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color == "Blue") {
            actor_Hexahedron->GetProperty()->SetColor(0.0, 0.0, 1.0);
        }
        else if (color == "Yellow") {
            actor_Hexahedron->GetProperty()->SetColor(1.0, 1.0, 0.0);
        }
        else if (color == "Green") {
            actor_Hexahedron->GetProperty()->SetColor(0.0, 1.0, 0.0);
        }
        else if (color == "Magenta") {
            actor_Hexahedron->GetProperty()->SetColor(1.0, 0.0, 1.0);
        }
        else if (color == "Black") {
            actor_Hexahedron->GetProperty()->SetColor(0.0, 0.0, 0.0);
        }
        else if (color == "White") {
            actor_Hexahedron->GetProperty()->SetColor(1.0, 1.0, 1.0);
        }
        actor_Hexahedron->GetProperty()->SetLineWidth(thickness);
        // Add the actor to the renderer
        renderer->AddActor(actor_Hexahedron);
    }

    void Draw_Polygon() {

    }

    void Draw_Star(double radius, string color, int thickness) {
        // Number of points to approximate the star
        int numPoints = 5; // You can adjust this value to change the level of detail of the star

        // Generate points for the outer and inner points of the star
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        for (int i = 0; i <= numPoints; i++) {
            double angleOuter = i * (2 * vtkMath::Pi() / numPoints); // Angle for outer points
            double angleInner = angleOuter + (vtkMath::Pi() / numPoints); // Angle for inner points
            double xOuter = radius * cos(angleOuter);
            double yOuter = radius * sin(angleOuter);
            double xInner = (radius / 2) * cos(angleInner);
            double yInner = (radius / 2) * sin(angleInner);
            points->InsertNextPoint(xOuter, yOuter, 0.0); // Insert outer points
            points->InsertNextPoint(xInner, yInner, 0.0); // Insert inner points
        }

        // Update the line source with the generated points
        Star_Source->SetPoints(points);

        // Update the mapper with the new data
        mapper_Star->SetInputConnection(Star_Source->GetOutputPort());
        mapper_Star->Update();

        // Update the actor with the new mapper and properties
        actor_Star->SetMapper(mapper_Star);
        if (color == "Red") {
            actor_Star->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color == "Blue") {
            actor_Star->GetProperty()->SetColor(0.0, 0.0, 1.0);
        }
        else if (color == "Yellow") {
            actor_Star->GetProperty()->SetColor(1.0, 1.0, 0.0);
        }
        else if (color == "Green") {
            actor_Star->GetProperty()->SetColor(0.0, 1.0, 0.0);
        }
        else if (color == "Magenta") {
            actor_Star->GetProperty()->SetColor(1.0, 0.0, 1.0);
        }
        else if (color == "Black") {
            actor_Star->GetProperty()->SetColor(0.0, 0.0, 0.0);
        }
        else if (color == "White") {
            actor_Star->GetProperty()->SetColor(1.0, 1.0, 1.0);
        }
        actor_Star->GetProperty()->SetLineWidth(thickness);

        // Add the actor to the renderer
        renderer->AddActor(actor_Star);
    }

    void DrawLine(vtkGenericOpenGLRenderWindow* window) {
        vtkNew<vtkPointPicker> pointPicker; // Create a new instance of the VTK point picker
        mapper->SetInputConnection(lineSource->GetOutputPort()); // Set the input of the mapper to the output of the line source
        mapper->Update();
        actor->SetMapper(mapper); // Set the mapper for the actor
        vtkNew <MouseInteractorStylePP> style; // Create a new instance of a custom VTK interactor style
        /*vtkNew<vtkRenderer> renderer;*/
        renderer->AddActor(actor);
        window->AddRenderer(renderer);    //add renderer to window   
        window->GetInteractor()->SetPicker(pointPicker);    // connect between qt and vtk
        window->GetInteractor()->SetInteractorStyle(style);
        style->setlinesource(lineSource);
        style->setlineactor(actor);
        //vtkRenderWidget->update();    //update render
        window->Render();    // Render the window
    }

    void DrawPoly_Line() {

    }

    void Draw_Line(double x1_line, double y1_line, double x2_line, double y2_line, string color, int thickness) {
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(x1_line, y1_line, 0.0);
    points->InsertNextPoint(x2_line, y2_line, 0.0);

    // Set the points for the vtkLineSource
    lineSource->SetPoints(points);
    mapper->SetInputConnection(lineSource->GetOutputPort());
    mapper->Update();

    // Set the mapper to the actor and add it to the renderer
    actor->SetMapper(mapper);
    if (color == "Red") {
        actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
    }
    else if (color == "Blue") {
        actor->GetProperty()->SetColor(0.0, 0.0, 1.0);
    }
    else if (color == "Yellow") {
        actor->GetProperty()->SetColor(1.0, 1.0, 0.0);
    }
    else if (color == "Green") {
        actor->GetProperty()->SetColor(0.0, 1.0, 0.0);
    }
    else if (color == "Magenta") {
        actor->GetProperty()->SetColor(1.0, 0.0, 1.0);
    }
    else if (color == "Black") {
        actor->GetProperty()->SetColor(0.0, 0.0, 0.0);
    }
    else if (color == "White") {
        actor->GetProperty()->SetColor(1.0, 1.0, 1.0);
    }
    actor->GetProperty()->SetLineWidth(thickness);

    renderer->AddActor(actor);

}
    void Save(QComboBox* comboBox) {
        QString shape_name = comboBox->currentText();
        if (shape_name == "Circle") {
            //Get the color and thickness of the line
            double* color = actor->GetProperty()->GetColor();
            double thickness = actor->GetProperty()->GetLineWidth();
            string color_name;
            // Get the name of the color based on its RGB value
            if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Red";
            }
            else if (color[0] == 0.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Green";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Blue";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Yellow";
            }
            else if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Magenta";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Black";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 1.0) {
                color_name = "White";
            }
            else {
                color_name = "Unknown";
            }
            // Ask user for TXT or CSV
            QMessageBox messageBox;
            messageBox.setText("Choose Save Type");
            QAbstractButton* filledButton = messageBox.addButton(QMessageBox::tr("TXT"), QMessageBox::YesRole);
            QAbstractButton* nonFilledButton = messageBox.addButton(QMessageBox::tr("CSV"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            std::string mode = buttonText.toStdString();
            if (mode == "TXT") {
                QString filename_txt = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text files (*.txt)");
                if (!filename_txt.isEmpty()) {
                    // Open the TXT output file for writing
                    std::ofstream outputFile_txt(filename_txt.toStdString());
                    outputFile_txt << "Shape\tRadius\tColor\tThickness" << std::endl;
                    outputFile_txt << "Circle\t" << Radius_Circle << "\t" << color_name << "\t" << thickness << std::endl;
                    outputFile_txt.close();
                }
            }
            else {
                QString filename_csv = QFileDialog::getSaveFileName(nullptr, "Save File", "", "CSV files (*.csv)");
                if (!filename_csv.isEmpty()) {
                    // Open the CSV output file for writing
                    std::ofstream outputFile_csv(filename_csv.toStdString());
                    outputFile_csv << "Shape,Radius,Color,Thickness" << std::endl;
                    outputFile_csv << "Circle," << Radius_Circle << "," << color_name << "," << thickness << std::endl;
                    outputFile_csv.close();
                }

            }
        }
        else if (shape_name == "Sphere") {
            //Get the color and thickness of the line
            double* color = actor->GetProperty()->GetColor();
            double thickness = actor->GetProperty()->GetLineWidth();
            string color_name;
            // Get the name of the color based on its RGB value
            if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Red";
            }
            else if (color[0] == 0.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Green";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Blue";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Yellow";
            }
            else if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Magenta";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Black";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 1.0) {
                color_name = "White";
            }
            else {
                color_name = "Unknown";
            }
            // Ask user for TXT or CSV
            QMessageBox messageBox;
            messageBox.setText("Choose Save Type");
            QAbstractButton* filledButton = messageBox.addButton(QMessageBox::tr("TXT"), QMessageBox::YesRole);
            QAbstractButton* nonFilledButton = messageBox.addButton(QMessageBox::tr("CSV"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            std::string mode = buttonText.toStdString();
            if (mode == "TXT") {
                QString filename_txt = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text files (*.txt)");
                if (!filename_txt.isEmpty()) {
                    // Open the TXT output file for writing
                    std::ofstream outputFile_txt(filename_txt.toStdString());
                    outputFile_txt << "Shape\tRadius\tColor\tThickness" << std::endl;
                    outputFile_txt << "Sphere\t" << Radius_Sphere << "\t" << color_name << "\t" << thickness << std::endl;
                    outputFile_txt.close();
                }
            }
            else {
                QString filename_csv = QFileDialog::getSaveFileName(nullptr, "Save File", "", "CSV files (*.csv)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_csv.isEmpty()) {
                    // Open the CSV output file for writing
                    std::ofstream outputFile_csv(filename_csv.toStdString());
                    outputFile_csv << "Shape,Radius,Color,Thickness" << std::endl;
                    outputFile_csv << "Sphere," << Radius_Sphere << "," << color_name << "," << thickness << std::endl;
                    outputFile_csv.close();
                }
            }
        }
        else if (shape_name == "Arc") {
            //Get the color and thickness of the line
            double* color = actor->GetProperty()->GetColor();
            double thickness = actor->GetProperty()->GetLineWidth();
            string color_name;
            // Get the name of the color based on its RGB value
            if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Red";
            }
            else if (color[0] == 0.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Green";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Blue";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Yellow";
            }
            else if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Magenta";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Black";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 1.0) {
                color_name = "White";
            }
            else {
                color_name = "Unknown";
            }
            // Ask user for TXT or CSV
            QMessageBox messageBox;
            messageBox.setText("Choose Save Type");
            QAbstractButton* filledButton = messageBox.addButton(QMessageBox::tr("TXT"), QMessageBox::YesRole);
            QAbstractButton* nonFilledButton = messageBox.addButton(QMessageBox::tr("CSV"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            std::string mode = buttonText.toStdString();
            if (mode == "TXT") {
                QString filename_txt = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text files (*.txt)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_txt.isEmpty()) {
                    // Open the TXT output file for writing
                    std::ofstream outputFile_txt(filename_txt.toStdString());
                    outputFile_txt << "Shape\tRadius\tColor\tThickness" << std::endl;
                    outputFile_txt << "Arc\t" << Radius_Arc << "\t" << color_name << "\t" << thickness << std::endl;
                    outputFile_txt.close();
                }
            }
            else {
                QString filename_csv = QFileDialog::getSaveFileName(nullptr, "Save File", "", "CSV files (*.csv)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_csv.isEmpty()) {
                    // Open the CSV output file for writing
                    std::ofstream outputFile_csv(filename_csv.toStdString());
                    outputFile_csv << "Shape,Radius,Color,Thickness" << std::endl;
                    outputFile_csv << "Arc," << Radius_Arc << "," << color_name << "," << thickness << std::endl;
                    outputFile_csv.close();
                }
            }
        }
        else if (shape_name == "Hexahedron") {
            //Get the color and thickness 
            double* color = actor->GetProperty()->GetColor();
            double thickness = actor->GetProperty()->GetLineWidth();
            string color_name;
            // Get the name of the color based on its RGB value
            if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Red";
            }
            else if (color[0] == 0.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Green";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Blue";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Yellow";
            }
            else if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Magenta";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Black";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 1.0) {
                color_name = "White";
            }
            else {
                color_name = "Unknown";
            }
            // Ask user for TXT or CSV
            QMessageBox messageBox;
            messageBox.setText("Choose Save Type");
            QAbstractButton* filledButton = messageBox.addButton(QMessageBox::tr("TXT"), QMessageBox::YesRole);
            QAbstractButton* nonFilledButton = messageBox.addButton(QMessageBox::tr("CSV"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            std::string mode = buttonText.toStdString();
            if (mode == "TXT") {
                QString filename_txt = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text files (*.txt)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_txt.isEmpty()) {
                    // Open the TXT output file for writing
                    std::ofstream outputFile_txt(filename_txt.toStdString());
                    outputFile_txt << "Shape\t\tRadius\tColor\tThickness" << std::endl;
                    outputFile_txt << "Hexahedron\t" << Radius_Hexahedron << "\t" << color_name << "\t" << thickness << std::endl;
                    outputFile_txt.close();
                }
            }
            else {
                QString filename_csv = QFileDialog::getSaveFileName(nullptr, "Save File", "", "CSV files (*.csv)");

                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_csv.isEmpty()) {
                    // Open the CSV output file for writing
                    std::ofstream outputFile_csv(filename_csv.toStdString());
                    outputFile_csv << "Shape,Radius,Color,Thickness" << std::endl;
                    outputFile_csv << "Hexahedron," << Radius_Hexahedron << "," << color_name << "," << thickness << std::endl;
                    outputFile_csv.close();
                }
            }
        }
        else if (shape_name == "Square") {
            //Get the color and thickness 
            double* color = actor->GetProperty()->GetColor();
            double thickness = actor->GetProperty()->GetLineWidth();
            string color_name;
            // Get the name of the color based on its RGB value
            if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Red";
            }
            else if (color[0] == 0.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Green";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Blue";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Yellow";
            }
            else if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Magenta";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Black";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 1.0) {
                color_name = "White";
            }
            else {
                color_name = "Unknown";
            }
            // Ask user for TXT or CSV
            QMessageBox messageBox;
            messageBox.setText("Choose Save Type");
            QAbstractButton* filledButton = messageBox.addButton(QMessageBox::tr("TXT"), QMessageBox::YesRole);
            QAbstractButton* nonFilledButton = messageBox.addButton(QMessageBox::tr("CSV"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            std::string mode = buttonText.toStdString();
            if (mode == "TXT") {
                QString filename_txt = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text files (*.txt)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_txt.isEmpty()) {
                    // Open the TXT output file for writing
                    std::ofstream outputFile_txt(filename_txt.toStdString());
                    outputFile_txt << "Shape\tRadius\tColor\tThickness" << std::endl;
                    outputFile_txt << "Square\t" << Radius_Square << "\t" << color_name << "\t" << thickness << std::endl;
                    outputFile_txt.close();
                }
            }
            else {
                QString filename_csv = QFileDialog::getSaveFileName(nullptr, "Save File", "", "CSV files (*.csv)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_csv.isEmpty()) {
                    // Open the CSV output file for writing
                    std::ofstream outputFile_csv(filename_csv.toStdString());
                    outputFile_csv << "Shape,Radius,Color,Thickness" << std::endl;
                    outputFile_csv << "Square," << Radius_Square << "," << color_name << "," << thickness << std::endl;
                    outputFile_csv.close();
                }
            }
        }
        else if (shape_name == "Regular Polygon") {
            //Get the color and thickness 
            double* color = actor->GetProperty()->GetColor();
            double thickness = actor->GetProperty()->GetLineWidth();
            string color_name;
            // Get the name of the color based on its RGB value
            if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Red";
            }
            else if (color[0] == 0.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Green";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Blue";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Yellow";
            }
            else if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Magenta";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Black";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 1.0) {
                color_name = "White";
            }
            else {
                color_name = "Unknown";
            }
            // Ask user for TXT or CSV
            QMessageBox messageBox;
            messageBox.setText("Choose Save Type");
            QAbstractButton* filledButton = messageBox.addButton(QMessageBox::tr("TXT"), QMessageBox::YesRole);
            QAbstractButton* nonFilledButton = messageBox.addButton(QMessageBox::tr("CSV"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            std::string mode = buttonText.toStdString();
            if (mode == "TXT") {
                QString filename_txt = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text files (*.txt)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_txt.isEmpty()) {
                    // Open the TXT output file for writing
                    std::ofstream outputFile_txt(filename_txt.toStdString());
                    outputFile_txt << "Shape\t\t\tRadius\tNumber of sides\tColor\tThickness" << std::endl;
                    outputFile_txt << "Regular_Polygon\t" << "\t" << Radius_Reg_Polygon << "\t" << NO_POINTS << "\t\t" << color_name << "\t" << thickness << std::endl;
                    outputFile_txt.close();
                }
            }
            else {
                QString filename_csv = QFileDialog::getSaveFileName(nullptr, "Save File", "", "CSV files (*.csv)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_csv.isEmpty()) {
                    // Open the CSV output file for writing
                    std::ofstream outputFile_csv(filename_csv.toStdString());
                    outputFile_csv << "Shape,Radius,Number of sides,Color,Thickness" << std::endl;
                    outputFile_csv << "Regular Polygon," << Radius_Reg_Polygon << "," << NO_POINTS << "," << color_name << "," << thickness << std::endl;
                    outputFile_csv.close();
                }
            }
        }
        else if (shape_name == "Cylinder") {
            //Get the color and thickness of the line
            double* color = actor->GetProperty()->GetColor();
            double thickness = actor->GetProperty()->GetLineWidth();
            string color_name;
            // Get the name of the color based on its RGB value
            if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Red";
            }
            else if (color[0] == 0.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Green";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Blue";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Yellow";
            }
            else if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Magenta";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Black";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 1.0) {
                color_name = "White";
            }
            else {
                color_name = "Unknown";
            }
            // Ask user for TXT or CSV
            QMessageBox messageBox;
            messageBox.setText("Choose Save Type");
            QAbstractButton* filledButton = messageBox.addButton(QMessageBox::tr("TXT"), QMessageBox::YesRole);
            QAbstractButton* nonFilledButton = messageBox.addButton(QMessageBox::tr("CSV"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            std::string mode = buttonText.toStdString();
            if (mode == "TXT") {
                QString filename_txt = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text files (*.txt)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_txt.isEmpty()) {
                    // Open the TXT output file for writing
                    std::ofstream outputFile_txt(filename_txt.toStdString());
                    outputFile_txt << "Shape\t\tRadius\tHeight\tColor\tThickness" << std::endl;
                    outputFile_txt << "Cylinder\t" << Radius_Cylinder << "\t" << Height_Cylinder << "\t" << color_name << "\t" << thickness << std::endl;
                    outputFile_txt.close();
                }
            }
            else {
                QString filename_csv = QFileDialog::getSaveFileName(nullptr, "Save File", "", "CSV files (*.csv)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_csv.isEmpty()) {
                    // Open the CSV output file for writing
                    std::ofstream outputFile_csv(filename_csv.toStdString());
                    outputFile_csv << "Shape,Radius,Height,Color,Thickness" << std::endl;
                    outputFile_csv << "Cylinder," << Radius_Cylinder << "," << Height_Cylinder << "," << color_name << "," << thickness << std::endl;
                    outputFile_csv.close();
                }
            }
        }
        else if (shape_name == "Ellipse") {
            //Get the color and thickness of the line
            double* color = actor->GetProperty()->GetColor();
            double thickness = actor->GetProperty()->GetLineWidth();
            string color_name;
            // Get the name of the color based on its RGB value
            if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Red";
            }
            else if (color[0] == 0.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Green";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Blue";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Yellow";
            }
            else if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Magenta";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Black";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 1.0) {
                color_name = "White";
            }
            else {
                color_name = "Unknown";
            }
            // Ask user for TXT or CSV
            QMessageBox messageBox;
            messageBox.setText("Choose Save Type");
            QAbstractButton* filledButton = messageBox.addButton(QMessageBox::tr("TXT"), QMessageBox::YesRole);
            QAbstractButton* nonFilledButton = messageBox.addButton(QMessageBox::tr("CSV"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            std::string mode = buttonText.toStdString();
            if (mode == "TXT") {
                QString filename_txt = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text files (*.txt)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_txt.isEmpty()) {
                    // Open the TXT output file for writing
                    std::ofstream outputFile_txt(filename_txt.toStdString());
                    outputFile_txt << "Shape\tMajor Axis\tMinor Axis\tColor\tThickness" << std::endl;
                    outputFile_txt << "Ellipse\t" << MAJOR_AXIS << "\t\t" << MINOR_AXIS << "\t\t" << color_name << "\t" << thickness << std::endl;
                    outputFile_txt.close();
                }
            }
            else {
                QString filename_csv = QFileDialog::getSaveFileName(nullptr, "Save File", "", "CSV files (*.csv)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_csv.isEmpty()) {
                    // Open the CSV output file for writing
                    std::ofstream outputFile_csv(filename_csv.toStdString());
                    outputFile_csv << "Shape,Major Axis,Minor Axis,Color,Thickness" << std::endl;
                    outputFile_csv << "Ellipse," << MAJOR_AXIS << "," << MINOR_AXIS << "," << color_name << "," << thickness << std::endl;
                    outputFile_csv.close();
                }
            }
        }
        else if (shape_name == "Star") {
            //Get the color and thickness of the line
            double* color = actor->GetProperty()->GetColor();
            double thickness = actor->GetProperty()->GetLineWidth();
            string color_name;
            // Get the name of the color based on its RGB value
            if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Red";
            }
            else if (color[0] == 0.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Green";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Blue";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Yellow";
            }
            else if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Magenta";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Black";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 1.0) {
                color_name = "White";
            }
            else {
                color_name = "Unknown";
            }
            // Ask user for TXT or CSV
            QMessageBox messageBox;
            messageBox.setText("Choose Save Type");
            QAbstractButton* filledButton = messageBox.addButton(QMessageBox::tr("TXT"), QMessageBox::YesRole);
            QAbstractButton* nonFilledButton = messageBox.addButton(QMessageBox::tr("CSV"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            std::string mode = buttonText.toStdString();
            if (mode == "TXT") {
                QString filename_txt = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text files (*.txt)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_txt.isEmpty()) {
                    // Open the TXT output file for writing
                    std::ofstream outputFile_txt(filename_txt.toStdString());
                    outputFile_txt << "Shape\tRadius\tColor\tThickness" << std::endl;
                    outputFile_txt << "Star\t" << Radius_Star << "\t" << color_name << "\t" << thickness << std::endl;
                    outputFile_txt.close();
                }
            }
            else {
                QString filename_csv = QFileDialog::getSaveFileName(nullptr, "Save File", "", "CSV files (*.csv)");
                // If the user didn't cancel the file dialogs, write to the output files
                if (!filename_csv.isEmpty()) {
                    // Open the CSV output file for writing
                    std::ofstream outputFile_csv(filename_csv.toStdString());
                    outputFile_csv << "Shape,Radius,Color,Thickness" << std::endl;
                    outputFile_csv << "Star," << Radius_Star << "," << color_name << "," << thickness << std::endl;
                    outputFile_csv.close();
                }
            }
        }
        else if (shape_name == "Line") {
            //Get the color and thickness of the line
            double* color = actor->GetProperty()->GetColor();
            double thickness = actor->GetProperty()->GetLineWidth();
            string color_name;
            // Get the name of the color based on its RGB value
            if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Red";
            }
            else if (color[0] == 0.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Green";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Blue";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
                color_name = "Yellow";
            }
            else if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 1.0) {
                color_name = "Magenta";
            }
            else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 0.0) {
                color_name = "Black";
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 1.0) {
                color_name = "White";
            }
            else {
                color_name = "Unknown";
            }
            // Ask user for TXT or CSV
            QMessageBox messageBox;
            messageBox.setText("Choose Save Type");
            QAbstractButton* filledButton = messageBox.addButton(QMessageBox::tr("TXT"), QMessageBox::YesRole);
            QAbstractButton* nonFilledButton = messageBox.addButton(QMessageBox::tr("CSV"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            std::string mode = buttonText.toStdString();
            if (mode == "TXT") {
                if (mode_line == "Enter points")
                {
                    QString filename_txt = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text files (*.txt)");
                    if (!filename_txt.isEmpty()) {
                        // Open the TXT output file for writing
                        std::ofstream outputFile_txt(filename_txt.toStdString());
                        outputFile_txt << "Shape\tX1\tY1\tX2\tY2\tColor\tThickness" << std::endl;
                        outputFile_txt << "Line\t" << x1_line << "\t" << y1_line << "\t" << x2_line << "\t" << y2_line << "\t" << color_name << "\t" << thickness << std::endl;
                        outputFile_txt.close();
                    }
                }
                else {

                }
            }
            else {
                if (mode_line == "Enter points")
                {
                    QString filename_csv = QFileDialog::getSaveFileName(nullptr, "Save File", "", "CSV files (*.csv)");
                    if (!filename_csv.isEmpty()) {
                        // Open the CSV output file for writing
                        std::ofstream outputFile_csv(filename_csv.toStdString());
                        outputFile_csv << "Shape,X1,Y1,X2,Y2,Color,Thickness" << std::endl;
                        outputFile_csv << "Line," << x1_line << "," << y1_line << "," << x2_line << "," << y2_line << "," << color_name << "," << thickness << std::endl;
                        outputFile_csv.close();
                    }
                }
            }
        }
    }

    void ChangeColor(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window) {
        QString color_name = comboBox->currentText();
        if (color_name == "Red")
        {
            actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
            actor_circle->GetProperty()->SetColor(1.0, 0.0, 0.0);
            actor_Ellipse->GetProperty()->SetColor(1.0, 0.0, 0.0);
            actor_Regular_Polygon->GetProperty()->SetColor(1.0, 0.0, 0.0);
            actor_Arc->GetProperty()->SetColor(1.0, 0.0, 0.0);
            actor_Cylinder->GetProperty()->SetColor(1.0, 0.0, 0.0);
            actor_Football->GetProperty()->SetColor(1.0, 0.0, 0.0);
            actor_Square->GetProperty()->SetColor(1.0, 0.0, 0.0);
            actor_Hexahedron->GetProperty()->SetColor(1.0, 0.0, 0.0);
            actor_Star->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color_name == "Green")
        {
            actor->GetProperty()->SetColor(0.0, 1.0, 0.0);
            actor_circle->GetProperty()->SetColor(0.0, 1.0, 0.0);
            actor_Ellipse->GetProperty()->SetColor(0.0, 1.0, 0.0);
            actor_Regular_Polygon->GetProperty()->SetColor(0.0, 1.0, 0.0);
            actor_Arc->GetProperty()->SetColor(0.0, 1.0, 0.0);
            actor_Cylinder->GetProperty()->SetColor(0.0, 1.0, 0.0);
            actor_Football->GetProperty()->SetColor(0.0, 1.0, 0.0);
            actor_Square->GetProperty()->SetColor(0.0, 1.0, 0.0);
            actor_Hexahedron->GetProperty()->SetColor(0.0, 1.0, 0.0);
            actor_Star->GetProperty()->SetColor(0.0, 1.0, 0.0);

        }
        else if (color_name == "Blue")
        {
            actor->GetProperty()->SetColor(0.0, 0.0, 1.0);
            actor_circle->GetProperty()->SetColor(0.0, 0.0, 1.0);
            actor_Ellipse->GetProperty()->SetColor(0.0, 0.0, 1.0);
            actor_Regular_Polygon->GetProperty()->SetColor(0.0, 0.0, 1.0);
            actor_Arc->GetProperty()->SetColor(0.0, 0.0, 1.0);
            actor_Cylinder->GetProperty()->SetColor(0.0, 0.0, 1.0);
            actor_Football->GetProperty()->SetColor(0.0, 0.0, 1.0);
            actor_Square->GetProperty()->SetColor(0.0, 0.0, 1.0);
            actor_Hexahedron->GetProperty()->SetColor(0.0, 0.0, 1.0);
            actor_Star->GetProperty()->SetColor(0.0, 0.0, 1.0);

        }
        else if (color_name == "Yellow")
        {
            actor->GetProperty()->SetColor(1.0, 1.0, 0.0);
            actor_circle->GetProperty()->SetColor(1.0, 1.0, 0.0);
            actor_Ellipse->GetProperty()->SetColor(1.0, 1.0, 0.0);
            actor_Regular_Polygon->GetProperty()->SetColor(1.0, 1.0, 0.0);
            actor_Arc->GetProperty()->SetColor(1.0, 1.0, 0.0);
            actor_Cylinder->GetProperty()->SetColor(1.0, 1.0, 0.0);
            actor_Football->GetProperty()->SetColor(1.0, 1.0, 0.0);
            actor_Square->GetProperty()->SetColor(1.0, 1.0, 0.0);
            actor_Hexahedron->GetProperty()->SetColor(1.0, 1.0, 0.0);
            actor_Star->GetProperty()->SetColor(1.0, 1.0, 0.0);

        }
        else if (color_name == "Magenta")
        {
            actor->GetProperty()->SetColor(1.0, 0.0, 1.0);
            actor_circle->GetProperty()->SetColor(1.0, 0.0, 1.0);
            actor_Ellipse->GetProperty()->SetColor(1.0, 0.0, 1.0);
            actor_Regular_Polygon->GetProperty()->SetColor(1.0, 0.0, 1.0);
            actor_Arc->GetProperty()->SetColor(1.0, 0.0, 1.0);
            actor_Cylinder->GetProperty()->SetColor(1.0, 0.0, 1.0);
            actor_Football->GetProperty()->SetColor(1.0, 0.0, 1.0);
            actor_Square->GetProperty()->SetColor(1.0, 0.0, 1.0);
            actor_Hexahedron->GetProperty()->SetColor(1.0, 0.0, 1.0);
            actor_Star->GetProperty()->SetColor(1.0, 0.0, 1.0);

        }
        else if (color_name == "Black")
        {
            actor->GetProperty()->SetColor(0.0, 0.0, 0.0);
            actor_circle->GetProperty()->SetColor(0.0, 0.0, 0.0);
            actor_Ellipse->GetProperty()->SetColor(0.0, 0.0, 0.0);
            actor_Regular_Polygon->GetProperty()->SetColor(0.0, 0.0, 0.0);
            actor_Arc->GetProperty()->SetColor(0.0, 0.0, 0.0);
            actor_Cylinder->GetProperty()->SetColor(0.0, 0.0, 0.0);
            actor_Football->GetProperty()->SetColor(0.0, 0.0, 0.0);
            actor_Square->GetProperty()->SetColor(0.0, 0.0, 0.0);
            actor_Hexahedron->GetProperty()->SetColor(0.0, 0.0, 0.0);
            actor_Star->GetProperty()->SetColor(0.0, 0.0, 0.0);

        }
        else if (color_name == "White")
        {
            actor->GetProperty()->SetColor(1.0, 1.0, 1.0);
            actor_circle->GetProperty()->SetColor(1.0, 1.0, 1.0);
            actor_Ellipse->GetProperty()->SetColor(1.0, 1.0, 1.0);
            actor_Regular_Polygon->GetProperty()->SetColor(1.0, 1.0, 1.0);
            actor_Arc->GetProperty()->SetColor(1.0, 1.0, 1.0);
            actor_Cylinder->GetProperty()->SetColor(1.0, 1.0, 1.0);
            actor_Football->GetProperty()->SetColor(1.0, 1.0, 1.0);
            actor_Square->GetProperty()->SetColor(1.0, 1.0, 1.0);
            actor_Hexahedron->GetProperty()->SetColor(1.0, 1.0, 1.0);
            actor_Star->GetProperty()->SetColor(1.0, 1.0, 1.0);

        }
        window->Render();
    }

    void Load()
    {
        QString filename = QFileDialog::getOpenFileName(nullptr, "Open File", "", "Text files (*.txt);;CSV files (*.csv)");

        if (!filename.isEmpty()) {
            // Check file extension
            QString fileExtension = QFileInfo(filename).suffix();
            if (fileExtension == "txt") {
                // Open the input file for reading
                std::ifstream inputFile(filename.toStdString());
                if (!inputFile.is_open()) {
                    std::cout << "Error opening file " << filename.toStdString() << std::endl;
                    return;
                }

                // Read the first line (header)
                std::string line;
                std::getline(inputFile, line);

                // Read the second line (data)
                std::getline(inputFile, line);
                std::istringstream iss(line);
                std::string shape;
                double radius;
                double cylinder_height;
                double major_axis;
                double minor_axis;
                double x1, y1, x2, y2; //// For Line
                int no_of_sides;
                std::string color_name;
                double thickness;
                iss >> shape;
                if (shape == "Circle") {
                    iss >> radius >> color_name >> thickness;
                    Draw_circle(radius, color_name, thickness);
                }
                else if (shape == "Sphere") {
                    iss >> radius >> color_name >> thickness;
                    Draw_Football(radius, color_name, thickness);
                }
                else if (shape == "Arc") {
                    iss >> radius >> color_name >> thickness;
                    Draw_Arc(radius, color_name, thickness);
                }
                else if (shape == "Hexahedron") {
                    iss >> radius >> color_name >> thickness;
                    Draw_Hexahedron(radius, color_name, thickness);
                }
                else if (shape == "Regular_Polygon") {
                    iss >> radius >> no_of_sides >> color_name >> thickness;
                    Draw_Regular_Polygon(radius, no_of_sides, color_name, thickness);
                }
                else if (shape == "Square") {
                    iss >> radius >> color_name >> thickness;
                    Draw_Square(radius, color_name, thickness);
                }
                else if (shape == "Cylinder") {
                    iss >> radius >> cylinder_height >> color_name >> thickness;
                    Draw_Cylinder(radius, cylinder_height, color_name, thickness);
                }
                else if (shape == "Ellipse") {
                    iss >> major_axis >> minor_axis >> color_name >> thickness;
                    Draw_Ellipse(major_axis, minor_axis, color_name, thickness);
                }
                else if (shape == "Star") {
                    iss >> radius >> color_name >> thickness;
                    Draw_Star(radius, color_name, thickness);
                }
                else if (shape == "Line") {
                    iss >> x1 >> y1 >> x2 >> y2 >> color_name >> thickness;
                    Draw_Line(x1, y1, x2, y2, color_name, thickness);
                }
                // Close the input file
                inputFile.close();
            }
            else if (fileExtension == "csv") {
                // Open the input file for reading
                QFile file(filename);
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    qDebug() << "Failed to open the file";
                    return;
                }

                QTextStream in(&file);
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    QStringList fields = line.split(","); // assuming comma as the delimiter
                    if (fields.size() < 2) {
                        qDebug() << "Invalid CSV line: " << line;
                        continue;
                    }

                    QString shape = fields[0];
                    if (shape == "Circle") {
                        double radius = fields[1].toDouble();
                        std::string color_name = fields.value(2).toStdString();
                        double thickness = fields[3].toDouble();
                        Draw_circle(radius, color_name, thickness);
                    }
                    else if (shape == "Sphere") {
                        double radius = fields[1].toDouble();
                        std::string color_name = fields.value(2).toStdString();
                        double thickness = fields[3].toDouble();
                        Draw_Football(radius, color_name, thickness);
                    }
                    else if (shape == "Arc") {
                        double radius = fields[1].toDouble();
                        std::string color_name = fields.value(2).toStdString();
                        double thickness = fields[3].toDouble();
                        Draw_Arc(radius, color_name, thickness);
                    }
                    else if (shape == "Hexahedron") {
                        double radius = fields[1].toDouble();
                        std::string color_name = fields.value(2).toStdString();
                        double thickness = fields[3].toDouble();
                        Draw_Hexahedron(radius, color_name, thickness);
                    }
                    else if (shape == "Regular_Polygon") {
                        double radius = fields[1].toDouble();
                        int no_of_sides = fields[2].toInt();
                        std::string color_name = fields.value(2).toStdString();
                        double thickness = fields[4].toDouble();
                        Draw_Regular_Polygon(radius, no_of_sides, color_name, thickness);
                    }
                    else if (shape == "Square") {
                        double radius = fields[1].toDouble();
                        std::string color_name = fields.value(2).toStdString();
                        double thickness = fields[3].toDouble();
                        Draw_Square(radius, color_name, thickness);
                    }
                    else if (shape == "Cylinder") {
                        double radius = fields[1].toDouble();
                        double cylinder_height = fields[2].toDouble();
                        std::string color_name = fields.value(2).toStdString();
                        double thickness = fields[4].toDouble();
                        Draw_Cylinder(radius, cylinder_height, color_name, thickness);
                    }
                    else if (shape == "Ellipse") {
                        double major_axis = fields[1].toDouble();
                        double minor_axis = fields[2].toDouble();
                        std::string color_name = fields.value(2).toStdString();
                        double thickness = fields[4].toDouble();
                        Draw_Ellipse(major_axis, minor_axis, color_name, thickness);
                    }
                    else if (shape == "Star") {
                        double radius = fields[1].toDouble();
                        std::string color_name = fields.value(2).toStdString();
                        double thickness = fields[3].toDouble();
                        Draw_Star(radius, color_name, thickness);
                    }
                    else if (shape == "Line") {
                        double x1 = fields[1].toDouble();
                        double y1 = fields[2].toDouble();
                        double x2 = fields[3].toDouble();
                        double y2 = fields[4].toDouble();
                        std::string color_name = fields.value(2).toStdString();
                        double thickness = fields[6].toDouble();
                        Draw_Line(x1, y1, x2, y2, color_name, thickness);
                    }
                    else {
                        qDebug() << "Unknown shape: " << shape;
                    }
                }

                file.close();
            }
            else {
                // Unsupported file type
                std::cout << "Error: Unsupported file type" << std::endl;
                return;
            }
        }
    }


    void UpdateLineThickness(int thickness, vtkGenericOpenGLRenderWindow* window) {
        actor->GetProperty()->SetLineWidth(thickness);
        actor->GetMapper()->Update();
        actor_Regular_Polygon->GetProperty()->SetLineWidth(thickness);
        actor_Regular_Polygon->GetMapper()->Update();
        actor_circle->GetProperty()->SetLineWidth(thickness);
        actor_circle->GetMapper()->Update();
        actor_Ellipse->GetProperty()->SetLineWidth(thickness);
        actor_Ellipse->GetMapper()->Update();
        actor_Arc->GetProperty()->SetLineWidth(thickness);
        actor_Arc->GetMapper()->Update();
        actor_Cylinder->GetProperty()->SetLineWidth(thickness);
        actor_Cylinder->GetMapper()->Update();
        actor_Football->GetProperty()->SetLineWidth(thickness);
        actor_Football->GetMapper()->Update();
        actor_Square->GetProperty()->SetLineWidth(thickness);
        actor_Square->GetMapper()->Update();
        actor_Hexahedron->GetProperty()->SetLineWidth(thickness);
        actor_Hexahedron->GetMapper()->Update();
        actor_Star->GetProperty()->SetLineWidth(thickness);
        actor_Star->GetMapper()->Update();
        window->Render();
    }

    void Change_Shapes(QComboBox* comboBox,
        vtkGenericOpenGLRenderWindow* window)
    {
        QString shape_name = comboBox->currentText();


        if (shape_name == "Circle")
        {
            bool ok;
            Radius_Circle = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the circle:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            Draw_circle(Radius_Circle, "Red", 1.0);
        }
        else if (shape_name == "Sphere") {
            bool ok;
            Radius_Sphere = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Sphere:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            Draw_Football(Radius_Sphere, "Red", 1.0);
        }
        else if (shape_name == "Arc")
        {
            bool ok;
            Radius_Arc = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Arc:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            Draw_Arc(Radius_Arc, "Red", 1.0);
        }
        else if (shape_name == "Hexahedron")
        {
            bool ok;
            Radius_Hexahedron = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Hexahedron:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            Draw_Hexahedron(Radius_Hexahedron, "Red", 1.0);
        }
        else if (shape_name == "Line")
        {
            Line_Poly = true;
            // Ask user for filled or non-filled region
            QMessageBox messageBox;
            messageBox.setText("Choose Drawning Style");
            QAbstractButton* filledButton = messageBox.addButton(QMessageBox::tr("Mouse Click"), QMessageBox::YesRole);
            QAbstractButton* nonFilledButton = messageBox.addButton(QMessageBox::tr("Enter points"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            mode_line = buttonText.toStdString();
            if (mode_line == "Enter points") {
                bool ok;
                x1_line = QInputDialog::getDouble(nullptr, "Enter Point 1", "Enter the X-Coordinate of the Line:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                y1_line = QInputDialog::getDouble(nullptr, "Enter Point 1", "Enter the Y-Coordinate of the Line:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                x2_line = QInputDialog::getDouble(nullptr, "Enter Point 2", "Enter the X-Coordinate of the Line:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                y2_line = QInputDialog::getDouble(nullptr, "Enter Point 2", "Enter the Y-Coordinate of the Line:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                Draw_Line(x1_line, y1_line, x2_line, y2_line, "Red", 1.0);
            }
            else {
                DrawLine(window);
            }
        }
        else if (shape_name == "Polyline")
        {

        }
        else if (shape_name == "Polygon") {
            is_Polygon == true;
            Draw_Polygon();
        }
        else if (shape_name == "Regular Polygon")
        {
            bool ok;
            Radius_Reg_Polygon = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Regular Polygon:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            NO_POINTS = QInputDialog::getDouble(nullptr, "Enter Number of sides", "Enter number of sides of the Regular Polygon:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            Draw_Regular_Polygon(Radius_Reg_Polygon, NO_POINTS, "Red", 1.0);
        }
        else if (shape_name == "Cylinder") {
            bool ok;
            Radius_Cylinder = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Cylinder:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            Height_Cylinder = QInputDialog::getDouble(nullptr, "Enter Height", "Enter the height of the Cylinder:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            Draw_Cylinder(Radius_Cylinder, Height_Cylinder, "Red", 1.0);
        }
        else if (shape_name == "Ellipse") {
            bool ok;
            MAJOR_AXIS = QInputDialog::getDouble(nullptr, "Enter Major Axis", "Enter the major axis (x) of the Ellipse:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            MINOR_AXIS = QInputDialog::getDouble(nullptr, "Enter Minor Axis", "Enter the minor axis (y) of the Ellipse:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            Draw_Ellipse(MAJOR_AXIS, MINOR_AXIS, "Red", 1.0);
        }
        else if (shape_name == "Square") {
            bool ok;
            Radius_Square = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Square:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            Draw_Square(Radius_Square, "Red", 1.0);
        }
        else if (shape_name == "Star") {
            bool ok;
            Radius_Star = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Star:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            Draw_Star(Radius_Star, "Red", 1.0);
        }

        window->Render();
    }
    void Delete(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window) {
        // Set the color of the shape to match the background color
        actor->GetProperty()->SetColor(renderer->GetBackground());
        // Remove points from the line source
        vtkSmartPointer<vtkPoints> emptyPoints = vtkSmartPointer<vtkPoints>::New();
        lineSource->SetPoints(emptyPoints);
        window->Render(); // Render the window to reflect the changes
    }
    void Transform(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window) {
        QString tranform_state = comboBox->currentText();
        if (tranform_state == "Translation") {

        }
    }
} // namespace