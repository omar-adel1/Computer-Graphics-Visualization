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
#include <set>
#include< QCheckBox.h>

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
#include <QListWidget>
#include <stack>
#include <iomanip> 
using namespace std;

vtkNew<vtkRenderer> renderer;
std::stack<vtkSmartPointer<vtkLineSource>> deleted_sources;
std::stack<vtkSmartPointer<vtkActor>> deleted_actors;
std::stack<std::string> drawn_shapes;

// Actor, Source, Mapper    FOR  Line
vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> lineSource = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  Circle
vtkSmartPointer<vtkActor> actor_circle = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_circle = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> circle_Source = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  Ellipse
vtkSmartPointer<vtkActor> actor_Ellipse = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Ellipse = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Ellipse_Source = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  Regular Polygon
vtkSmartPointer<vtkActor> actor_Regular_Polygon = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Regular_Polygon = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Regular_Polygon_Source = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  Arc
vtkSmartPointer<vtkActor> actor_Arc = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Arc = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Arc_Source = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  Cylinder
vtkSmartPointer<vtkActor> actor_Cylinder = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Cylinder = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Cylinder_Source = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  Sphere
vtkSmartPointer<vtkActor> actor_Football = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Football = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Football_Source = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  Square
vtkSmartPointer<vtkActor> actor_Square = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Square = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Square_Source = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  Hexahedron
vtkSmartPointer<vtkActor> actor_Hexahedron = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Hexahedron = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Hexahedron_Source = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  Star
vtkSmartPointer<vtkActor> actor_Star = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* mapper_Star = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Star_Source = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR Solving interactor
vtkSmartPointer<vtkActor> Delactor = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* Delmapper = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> DellineSource = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  Polygon
vtkSmartPointer<vtkActor> Polygon_actor = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* Polygon_mapper = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Polygon_Source = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  PolyLine
vtkSmartPointer<vtkActor> PolyLine_actor = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* PolyLine_mapper = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> PolyLine_Source = vtkSmartPointer<vtkLineSource>::New();
// Actor, Source, Mapper    FOR  Ellipsoid
vtkSmartPointer<vtkActor> Ellipsoid_actor = vtkSmartPointer<vtkActor>::New();
vtkDataSetMapper* Ellipsoid_mapper = vtkDataSetMapper::New();
vtkSmartPointer<vtkLineSource> Ellipsoid_Source = vtkSmartPointer<vtkLineSource>::New();
/*________________________________Global Initialization________________________________________*/
int NO_POINTS, NO_POINTS_polyline, NO_POINTS_polygon;
double Radius_Cylinder;
double Height_Cylinder;
double Radius_Hexahedron;
double Radius_Star;
double Radius_Rosette;
double Radius_Circle, center_x_circle, center_y_circle;    // Circle Parameters
double Radius_Sphere, center_x_sphere, center_y_sphere, center_z_sphere;    // Sphere Parameters
double MAJOR_AXIS, MINOR_AXIS, center_x_ellipse, center_y_ellipse;     // Ellipse Parameters
double Radius_Arc, center_x_arc, center_y_arc;      // Arc Parameters
double Radius_Square;    // Square Parameters
double Radius_Reg_Polygon, center_x_reg_polygon, center_y_reg_polygon;
double semi_axis_x, semi_axis_y, semi_axis_z;
bool sphere_3D = false;
bool cube_3D = false;
bool Ellipsoid_3D = false;
bool cylinder_3D = false;
double picked[3]; // Declares an array of 3 doubles called "picked"
string mode_line;
string mode_circle, mode_Sphere, mode_Ellipse, mode_arc;     /// Enter Points  OR  Mouse Click
string delete_mode;
string color_mode = "One Shape";
string Shearing_direc_mode;
string transform_mode;
string thickness_mode;
double x1_line, y1_line, x2_line, y2_line;
bool is_Polygon = false;
int num_vertices_ros;
set<QString> drawnShapes, drawnShapes_all;
int count_shapes = 0;
bool all_deleted = false;
bool circle_deleted = false;
bool ellipse_deleted = false;
bool Regular_Polygon_deleted = false;
bool Arc_deleted = false;
bool Cylinder_deleted = false;
bool Sphere_deleted = false;
bool Square_deleted = false;
bool Hexahedron_deleted = false;
bool Star_deleted = false;
bool line_deleted = false;
bool polyline_deleted = false;
bool Polygon_deleted = false;
bool Ellipsoid_deleted = false;
bool circle_mouse_enter = false;
bool ellipse_mouse_enter = false;
bool sphere_mouse_enter = false;
bool arc_mouse_enter = false;
bool line_mouse_enter = false;
/////////////// Storing each shape color in global variable to use it while saving it in external file (TXT,CSV) /////////
string Color_Line, Color_Circle, Color_Ellipse, Color_Star, Color_Hexahedron, Color_Square, Color_Sphere, Color_Cylinder, Color_Arc, Color_Polygon, Color_PolyLine, Color_Regular_Polygon, Color_Ellipsoid;

namespace {
    void DrawPolyLine(vtkSmartPointer<vtkPoints> points);

    void DeleteLine_Poly(vtkSmartPointer<vtkPoints> points);

    void DrawPolygon(vtkSmartPointer<vtkPoints> points);

    void DrawLine(vtkSmartPointer<vtkPoints> points);

    void DrawPolygon(vtkSmartPointer<vtkPoints> points);

    void Draw_circle(double radius, string color, int thickness, double center_x, double center_y);

    void Draw_Ellipse(double x_axis, double y_axis, string color, int thickness, double center_x, double center_y);

    void Draw_Arc(double radius, string color, int thickness, double center_x, double center_y, double start_angle, double end_angle);

    void Draw_Cylinder(double radius, double height, string color, int thickness);

    void Draw_Sphere(double radius, string color, int thickness, double center_x, double center_y, double center_z);

    void Draw_Square(double radius_square, string color, int thickness);

    void Draw_Hexahedron(double radius_hex, string color, int thickness);

    void Draw_Ellipsoid(double a, double b, double c, string color, int thickness);

    void Draw_Star(double radius, string color, int thickness);

    void Draw_Regular_Polygon(double radius, int no_points, string color, int thickness);

    void Change_Shapes(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window, QListWidget& shapeListWidget);

    void ChangeColor_Button(QComboBox* comboBox_Color, vtkGenericOpenGLRenderWindow* window, QComboBox* comboBox_Shapes);

    void UpdateThickness(int thickness, vtkGenericOpenGLRenderWindow* window, QComboBox* comboBox);

    void Save();

    void Delete(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window);

    void Transform(QComboBox* comboBox_Transform, vtkGenericOpenGLRenderWindow* window, QComboBox* comboBox_Shapes);

    void Load(QComboBox* comboBox);

    void Undo(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window);

    void Redo(vtkGenericOpenGLRenderWindow* window);

    void Add_shape_list(QComboBox* shapeListComboBox);
} // namespace

namespace {
    class MouseInteractorStyleDrawLine : public vtkInteractorStyleTrackballCamera
    {
    public:
        static MouseInteractorStyleDrawLine* New();
        vtkTypeMacro(MouseInteractorStyleDrawLine, vtkInteractorStyleTrackballCamera);

        MouseInteractorStyleDrawLine()
        {
            this->Points = vtkSmartPointer<vtkPoints>::New();
            this->Picker = vtkSmartPointer<vtkPointPicker>::New();

            this->numofpoints = NULL;
        }

        virtual void OnLeftButtonDown() override
        {

            this->Picker->Pick(this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1], this->Interactor->GetEventPosition()[2], this->Renderer);
            double picked[3];
            this->Picker->GetPickPosition(picked);

            // Add a text actor to show the clicked point
            vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
            std::string text = "Point: (" + std::to_string(picked[0]) + ", " + std::to_string(picked[1]) + "," + std::to_string(picked[2]) + ") ";
            textActor->SetInput(text.c_str());
            textActor->SetDisplayPosition(this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1]);
            vtkPropCollection* actors = renderer->GetViewProps();
            actors->InitTraversal();
            vtkProp* actor = nullptr;
            while ((actor = actors->GetNextProp()) != nullptr) {
                vtkSmartPointer<vtkTextActor> textProp = vtkTextActor::SafeDownCast(actor);
                if (textProp) {
                    renderer->RemoveActor2D(textProp);
                }
            }
            renderer->AddActor2D(textActor);
            this->Points->InsertNextPoint(picked);
            if (this->Drawflag) {
                // Draw the line
                if (this->Points->GetNumberOfPoints() > 2 && this->ShapeName == "Line")
                {
                    DrawLine(this->Points);
                    line_mouse_enter = true;
                }
                else if (this->ShapeName == "Polyline" && this->Points->GetNumberOfPoints() == NO_POINTS_polyline) {
                    DrawPolyLine(this->Points);
                }
                else if (this->ShapeName == "Polygon" && this->Points->GetNumberOfPoints() == NO_POINTS_polygon) {
                    DrawPolygon(this->Points);
                }
                else if (this->ShapeName == "Circle") {
                    if (mode_circle == "Enter points") {
                        Draw_circle(Radius_Circle, "Red", 1.0, 0, 0);
                        circle_mouse_enter = false;
                    }
                    else {
                        if (this->Points->GetNumberOfPoints() == 2) {
                            // Calculate the radius of the circle using the picked point and the previous point
                            double picked2[3];
                            this->Points->GetPoint(0, picked2);
                            center_x_circle = picked2[0];
                            center_y_circle = picked2[1];
                            this->Points->GetPoint(1, picked2);
                            Radius_Circle = sqrt(pow((picked2[0] - center_x_circle), 2.0) + pow(picked2[1] - center_y_circle, 2.0));
                            Draw_circle(Radius_Circle, "Red", 1.0, center_x_circle, center_y_circle);
                            circle_mouse_enter = true;
                        }
                    }
                }
                else if (this->ShapeName == "Sphere") {
                    if (mode_Sphere == "Enter points") {
                        Draw_Sphere(Radius_Sphere, "Red", 1.0, 0, 0, 0);
                        sphere_mouse_enter = false;
                    }
                    else {
                        if (this->Points->GetNumberOfPoints() == 2) {
                            // Calculate the radius of the sphere using the picked point and the previous point
                            double picked2[3];
                            this->Points->GetPoint(0, picked2);
                            center_x_sphere = picked2[0];
                            center_y_sphere = picked2[1];
                            center_z_sphere = picked2[2];
                            this->Points->GetPoint(1, picked2);
                            Radius_Sphere = sqrt(pow((picked2[0] - center_x_sphere), 2.0) + pow(picked2[1] - center_y_sphere, 2.0) + pow(picked2[2] - center_z_sphere, 2.0));
                            // Draw the sphere
                            Draw_Sphere(Radius_Sphere, "Red", 1.0, center_x_sphere, center_y_sphere, center_z_sphere);
                            sphere_mouse_enter = true;
                        }
                    }
                }
                else if (this->ShapeName == "Arc") {
                    if (mode_arc == "Enter points") {
                        Draw_Arc(Radius_Arc, "Red", 1.0, 0, 0, 1.0, vtkMath::Pi());
                        arc_mouse_enter = false;
                    }
                    else {
                        if (this->Points->GetNumberOfPoints() == 3) {
                            double picked[3];
                            this->Points->GetPoint(0, picked);
                            double center1[2] = { picked[0], picked[1] };
                            this->Points->GetPoint(1, picked);
                            double p1[2] = { picked[0], picked[1] };
                            this->Points->GetPoint(2, picked);
                            double p2[2] = { picked[0], picked[1] };

                            // Calculate the center of the circle that passes through the three points
                            double x1 = center1[0], y1 = center1[1];
                            double x2 = p1[0], y2 = p1[1];
                            double x3 = p2[0], y3 = p2[1];
                            double ma = (y2 - y1) / (x2 - x1);
                            double mb = (y3 - y2) / (x3 - x2);
                            center_x_arc = (ma * mb * (y1 - y3) + mb * (x1 + x2) - ma * (x2 + x3)) / (2 * (mb - ma));
                            center_y_arc = (-1 / ma) * (center_x_arc - (x1 + x2) / 2) + (y1 + y2) / 2;

                            // Calculate the start and end angles of the arc
                            double start_angle = atan2(p1[1] - center_y_arc, p1[0] - center_x_arc);
                            double end_angle = atan2(p2[1] - center_y_arc, p2[0] - center_x_arc);
                            Radius_Arc = sqrt(pow((p1[0] - center_x_arc), 2.0) + pow(p1[1] - center_y_arc, 2.0));

                            Draw_Arc(Radius_Arc, "Red", 1.0, center_x_arc, center_y_arc, start_angle, end_angle);
                            arc_mouse_enter = true;
                        }
                    }
                }
                else if (this->ShapeName == "Hexahedron") {
                    Draw_Hexahedron(Radius_Hexahedron, "Red", 1.0);
                }
                else if (this->ShapeName == "Regular Polygon") {
                    Draw_Regular_Polygon(Radius_Reg_Polygon, NO_POINTS, "Red", 1.0);
                }
                else if (this->ShapeName == "Cylinder") {
                    Draw_Cylinder(Radius_Cylinder, Height_Cylinder, "Red", 1.0);
                }
                else if (this->ShapeName == "Ellipse") {
                    if (mode_Ellipse == "Enter points") {
                        Draw_Ellipse(MAJOR_AXIS, MINOR_AXIS, "Red", 1.0, 0, 0);
                        ellipse_mouse_enter = false;
                    }
                    else {
                        if (this->Points->GetNumberOfPoints() == 3) {
                            double picked[3];
                            this->Points->GetPoint(0, picked);
                            center_x_ellipse = picked[0];
                            center_y_ellipse = picked[1];
                            this->Points->GetPoint(1, picked);
                            double major_x_diff = picked[0] - center_x_ellipse;
                            double major_y_diff = picked[1] - center_y_ellipse;
                            MAJOR_AXIS = sqrt(major_x_diff * major_x_diff + major_y_diff * major_y_diff);
                            this->Points->GetPoint(2, picked);
                            double minor_x_diff = picked[0] - center_x_ellipse;
                            double minor_y_diff = picked[1] - center_y_ellipse;
                            MINOR_AXIS = sqrt(minor_x_diff * minor_x_diff + minor_y_diff * minor_y_diff);
                            Draw_Ellipse(MAJOR_AXIS, MINOR_AXIS, "Red", 1.0, center_x_ellipse, center_y_ellipse);
                            ellipse_mouse_enter = true;
                        }

                    }
                }
                else if (this->ShapeName == "Square") {
                    Draw_Square(Radius_Square, "Red", 1.0);
                }
                else if (this->ShapeName == "Star") {
                    Draw_Star(Radius_Star, "Red", 1.0);
                }
                else if (this->ShapeName == "Ellipsoid") {
                    Draw_Ellipsoid(semi_axis_x, semi_axis_y, semi_axis_z, "Red", 1.0);
                }
            }
            else if (this->Transformflag == true) {


            }
            // Forward events
            vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
        }

        void DeleteLine() {
            LineSource->Delete();
            Mapper->Delete();
            Actor->Delete();
        }

        void SetRenderer(vtkRenderer* renderer)
        {
            this->Renderer = renderer;
        }
        void setDrawFlag(bool f) {
            this->Drawflag = f;
        }
        bool getFLag() {
            return Drawflag;
        }
        void setTransformFlag(bool f) {
            Transformflag = f;
        }
        void setPolygonFlag(bool f) {
            Polygonflag = f;
        }
        void setShapeName(std::string Sh) {
            ShapeName = Sh;
        }
        void SetRadius(double r) {
            Radius = r;
        }
        void SetPoints(vtkSmartPointer<vtkPoints> Points) {
            this->Points = Points;
        }
        vtkSmartPointer<vtkPoints> GetPoints() {
            return Points;
        }

    private:
        vtkSmartPointer<vtkPoints> Points;
        // vtkSmartPointer<vtkNamedColors> Color;
        vtkRenderer* Renderer;
        vtkSmartPointer<vtkPointPicker> Picker;
        vtkSmartPointer<vtkActor> Actor = vtkSmartPointer<vtkActor>::New();
        vtkDataSetMapper* Mapper = vtkDataSetMapper::New();
        vtkSmartPointer<vtkLineSource> LineSource = vtkSmartPointer<vtkLineSource>::New();
        std::string ShapeName;
        bool Drawflag;
        bool Transformflag;
        bool Polygonflag;
        double Radius;
        int numofpoints;
    };
    vtkStandardNewMacro(MouseInteractorStyleDrawLine);
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
    QPushButton* changeColorButton = new QPushButton("Add color");
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

    // Create a QLineEdit widget and set a placeholder text
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText("Enter the thickness");

    // Add the QLineEdit widget to the control dock layout
    dockLayout->addWidget(lineEdit);

    // Chooosing Shapes to draw button
    QPushButton* changeshapes = new QPushButton("Add Shape");
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
    shapesdroplist->addItem("Ellipsoid");
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

    // Undo Button
    QPushButton undo_button;
    undo_button.setText("Undo");
    dockLayout->addWidget(&undo_button);

    // Undo Button
    QPushButton redo_button;
    redo_button.setText("Redo");
    dockLayout->addWidget(&redo_button);

    // shape list dock
    // Initialize an empty QListWidget to store the drawn shapes
    QListWidget shapeListWidget;
    QDockWidget* shapeListDock = new QDockWidget("Shapes List", &mainWindow);
    shapeListDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    mainWindow.addDockWidget(Qt::RightDockWidgetArea, shapeListDock);

    QPointer<QVBoxLayout> shapeListLayout = new QVBoxLayout();
    QWidget* shapeListContainer = new QWidget();
    shapeListContainer->setLayout(shapeListLayout);
    shapeListDock->setWidget(shapeListContainer);
    shapeListLayout->addWidget(&shapeListWidget);

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
        [=, &shapesdroplist, &window, &shapeListWidget]() { Change_Shapes(shapesdroplist, window, shapeListWidget); });

    // Connect Change Color 
    QObject::connect(changeColorButton, &QPushButton::clicked,
        [=, &colorDroplist, &window]() { ChangeColor_Button(colorDroplist, window, shapesdroplist); });

    // Connect Change Thickness
    QObject::connect(lineEdit, &QLineEdit::returnPressed, [&]() {
        int thickness = lineEdit->text().toInt();
        UpdateThickness(thickness, window, shapesdroplist);
        });

    // Connect save button
    QObject::connect(&saveButton, &QPushButton::released,
        [&]() {  ::Save(); });

    // Connect upload button
    QObject::connect(&uploadButton, &QPushButton::released,
        [&]() {  ::Load(shapesdroplist); });

    // Connect Delete Button
    QObject::connect(delete_button, &QPushButton::clicked,
        [=, &shapesdroplist, &window]() { Delete(shapesdroplist, window); });

    // Connect Change Color 
    QObject::connect(trasform_button, &QPushButton::clicked,
        [=, &transform_list, &window]() { Transform(transform_list, window, shapesdroplist); });

    // Connect undo button
    QObject::connect(&undo_button, &QPushButton::released,
        [&]() {  ::Undo(shapesdroplist, window); });

    // Connect redo button
    QObject::connect(&redo_button, &QPushButton::released,
        [&]() {  ::Redo(window); });

    mainWindow.show();

    return app.exec();
}

namespace {
    void set_color_and_thickness(string color, int thickness, vtkSmartPointer<vtkActor> temp_actor) {
        /**
        1- This function sets the color and thickness of a vtkActor object based on the provided parameters.
        2- The function takes a string color parameter which represents the color of the actor. The available
        colors are Red, Blue, Yellow, Green, Magenta, Black, and White.
        3- The function also takes an integer thickness parameter which represents the thickness of the actor's
        lines.
        4- The function then sets the color and thickness of the provided vtkActor object accordingly.
        */

        if (color == "Red") {
            temp_actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color == "Blue") {
            temp_actor->GetProperty()->SetColor(0.0, 0.0, 1.0);
        }
        else if (color == "Yellow") {
            temp_actor->GetProperty()->SetColor(1.0, 1.0, 0.0);
        }
        else if (color == "Green") {
            temp_actor->GetProperty()->SetColor(0.0, 1.0, 0.0);
        }
        else if (color == "Magenta") {
            temp_actor->GetProperty()->SetColor(1.0, 0.0, 1.0);
        }
        else if (color == "Black") {
            temp_actor->GetProperty()->SetColor(0.0, 0.0, 0.0);
        }
        else if (color == "White") {
            temp_actor->GetProperty()->SetColor(1.0, 1.0, 1.0);
        }
        temp_actor->GetProperty()->SetLineWidth(thickness);
    }

    void Draw_circle(double radius, string color, int thickness, double center_x, double center_y)
    {
        /*
        * 1-This function generates a 2D circle with a given radius, center coordinates, color, and thickness using VTK library.
        * 2-It approximates the circle with a certain number of points and inserts them into a vtkPoints object.
        * 3-The vtkPoints object is then set to a vtkPolyData object that is used to update a vtkDataSetMapper object.
        * 4-Finally, the updated mapper is assigned to a vtkActor object that represents the circle and is added to a vtkRenderer object.
        */
        double R = radius; // Radius of the circle
        int numPoints = 50; // Number of points to approximate the circle

        lineSource->SetResolution(numPoints);
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Generate points on the circle using parametric equations
        for (int i = 0; i <= numPoints; i++)
        {
            double t = static_cast<double>(i) / numPoints;
            double x = center_x + R * cos(2 * vtkMath::Pi() * t);
            double y = center_y + R * sin(2 * vtkMath::Pi() * t);
            points->InsertNextPoint(x, y, 0.0); // Insert points on the circle
        }
        circle_Source->SetPoints(points);

        // Update the mapper with the new data
        mapper_circle->SetInputConnection(circle_Source->GetOutputPort());
        mapper_circle->Update();

        // Update the actor with the new mapper and properties based on user's choice
        actor_circle->SetMapper(mapper_circle);
        set_color_and_thickness(color, thickness, actor_circle);

        // Add the actor to the renderer
        renderer->AddActor(actor_circle);
    }

    void Draw_Ellipse(double x_axis, double y_axis, string color, int thickness, double center_x, double center_y) {
        // Create an ellipse using parametric equations
        double A = x_axis; // Major axis length
        double B = y_axis; // Minor axis length
        int numPoints = 50; // Number of points to approximate the ellipse

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        for (int i = 0; i <= numPoints; ++i) // Include the last point to complete the ellipse
        {
            double t = 2 * vtkMath::Pi() * static_cast<double>(i) / numPoints;
            double x = A * cos(t) + center_x;
            double y = B * sin(t) + center_y;
            points->InsertNextPoint(x, y, 0.0);
        }

        Ellipse_Source->SetPoints(points);

        mapper_Ellipse->SetInputConnection(Ellipse_Source->GetOutputPort());

        actor_Ellipse->SetMapper(mapper_Ellipse);
        set_color_and_thickness(color, thickness, actor_Ellipse);

        // Add the actor to the renderer
        renderer->AddActor(actor_Ellipse);
    }

    void Draw_Regular_Polygon(double radius, int no_points, string color, int thickness) {
        // Define parameters for the regular polygon
        double angleIncrement = 2 * vtkMath::Pi() / no_points; // Angle increment between consecutive points

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Generate points on the regular polygon using parametric equation
        for (int i = 0; i <= no_points; i++)
        {
            double angle = i * angleIncrement;
            double x = radius * cos(angle);
            double y = radius * sin(angle);
            points->InsertNextPoint(x, y, 0.0); // Insert points on the regular polygon
        }

        // Set the points as the input points for the line source
        Regular_Polygon_Source->SetPoints(points);

        // Update the mapper with the line source output
        mapper_Regular_Polygon->SetInputConnection(Regular_Polygon_Source->GetOutputPort());

        // Update the actor with the mapper and properties
        actor_Regular_Polygon->SetMapper(mapper_Regular_Polygon);
        set_color_and_thickness(color, thickness, actor_Regular_Polygon);

        // Add the actor to the renderer
        renderer->AddActor(actor_Regular_Polygon);
    }

    void Draw_Arc(double radius, string color, int thickness, double center_x, double center_y, double start_angle, double end_angle) {
        // Define parameters for the arc
        //double startAngle = 1.0; // Start angle of the arc in radians
        //double endAngle = vtkMath::Pi(); // End angle of the arc in radians
        int numPoints = 100; // Number of points to approximate the arc

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Generate points on the arc using parametric equation
        double angleIncrement = (end_angle - start_angle) / numPoints;
        for (int i = 0; i <= numPoints; i++)
        {
            double angle = start_angle + i * angleIncrement;
            double x = radius * cos(angle) + center_x;
            double y = radius * sin(angle) + center_y;
            points->InsertNextPoint(x, y, 0.0); // Insert points on the arc
        }

        // Set the points as the input points for the line source
        Arc_Source->SetPoints(points);

        // Update the mapper with the line source output
        mapper_Arc->SetInputConnection(Arc_Source->GetOutputPort());

        // Update the actor with the mapper and properties
        actor_Arc->SetMapper(mapper_Arc);
        set_color_and_thickness(color, thickness, actor_Arc);

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
        set_color_and_thickness(color, thickness, actor_Cylinder);

        // Add the actor to the renderer
        renderer->AddActor(actor_Cylinder);

    }

    void Draw_Sphere(double radius, string color, int thickness, double center_x, double center_y, double center_z) {
        // Define parameters for the sphere
        double R = radius; // Radius of the sphere
        int numPointsTheta = 100; // Number of points in theta direction
        int numPointsPhi = 50; // Number of points in phi direction

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Generate points on the sphere using parametric equations
        double thetaIncrement = 2 * vtkMath::Pi() / numPointsTheta; // Modified line
        double phiIncrement = 2 * vtkMath::Pi() / numPointsPhi;
        for (int i = 0; i <= numPointsTheta; i++)
        {
            double theta = i * thetaIncrement;
            for (int j = 0; j <= numPointsPhi; j++)
            {
                double phi = j * phiIncrement;
                double x = center_x + R * cos(phi) * cos(theta);
                double y = center_y + R * sin(phi) * cos(theta);
                double z = center_z + R * sin(theta);
                points->InsertNextPoint(x, y, z); // Insert points on the sphere
            }
        }

        // Set the points as the input points for the sphere source
        Football_Source->SetPoints(points);

        // Update the mapper with the sphere source output
        mapper_Football->SetInputConnection(Football_Source->GetOutputPort());

        // Update the actor with the mapper and properties
        actor_Football->SetMapper(mapper_Football);
        set_color_and_thickness(color, thickness, actor_Football);

        // Add the actor to the renderer
        renderer->AddActor(actor_Football);
    }

    void Draw_Square(double radius_square, string color, int thickness)
    {
        // Define the center point of the hexahedron
        double center[3] = { 0.0, 0.0, 0.0 };

        // Calculate the coordinates of the vertices of the upper part of the hexahedron
        double vertices[5][3] = { {center[0] - radius_square, center[1] - radius_square, 0},
                                    {center[0] - radius_square, center[1] + radius_square, 0},
                                    {center[0] + radius_square, center[1] + radius_square, 0},
                                    {center[0] + radius_square, center[1] - radius_square, 0},
                                    {center[0] - radius_square, center[1] - radius_square, 0} };

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Insert the vertices of the upper part of the hexahedron as points in the points array
        for (int i = 0; i < 5; i++)
        {
            points->InsertNextPoint(vertices[i]);
        }

        // Set the points and cells as the input data for the line source
        Square_Source->SetPoints(points);
        //lineSource->SetCells(VTK_HEXAHEDRON, hexahedronCells);

        // Update the mapper with the line source output
        mapper_Square->SetInputConnection(Square_Source->GetOutputPort());

        // Update the actor with the mapper and properties

        actor_Square->SetMapper(mapper_Square);
        set_color_and_thickness(color, thickness, actor_Square);

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
        set_color_and_thickness(color, thickness, actor_Hexahedron);

        // Add the actor to the renderer
        renderer->AddActor(actor_Hexahedron);
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
        set_color_and_thickness(color, thickness, actor_Star);

        // Add the actor to the renderer
        renderer->AddActor(actor_Star);
    }

    void Draw_Line(double x1_line, double y1_line, double x2_line, double y2_line, string color, int thickness) {
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        int numPoints = 2; // Number of points to approximate the line

        // Generate points on the line using parametric equations
        for (int i = 0; i <= numPoints; i++) {
            double t = static_cast<double>(i) / numPoints;
            double x = x1_line + t * (x2_line - x1_line);
            double y = y1_line + t * (y2_line - y1_line);
            points->InsertNextPoint(x, y, 0.0); // Insert points on the line
        }

        // Set the points for the vtkLineSource
        lineSource->SetPoints(points);
        mapper->SetInputConnection(lineSource->GetOutputPort());
        mapper->Update();

        // Set the mapper to the actor and add it to the renderer
        actor->SetMapper(mapper);
        set_color_and_thickness(color, thickness, actor);
        renderer->AddActor(actor);
    }

    void DrawLine(vtkSmartPointer<vtkPoints> points) {

        // Point 1
        double* point1 = points->GetPoint(points->GetNumberOfPoints() - 2);
        x1_line = floor(point1[0] * 100) / 100;
        y1_line = floor(point1[1] * 100) / 100;

        // Point 2
        double* point2 = points->GetPoint(points->GetNumberOfPoints() - 1);
        x2_line = floor(point2[0] * 100) / 100;
        y2_line = floor(point2[1] * 100) / 100;

        vtkSmartPointer<vtkPoints> linePoints = vtkSmartPointer<vtkPoints>::New();
        for (double t = 0; t <= 1; t += 0.01) {
            double x = x1_line + t * (x2_line - x1_line);
            double y = y1_line + t * (y2_line - y1_line);
            linePoints->InsertNextPoint(x, y, 0.0);
        }

        lineSource->SetPoints(linePoints);


        // Create a mapper and actor for the line
        mapper->SetInputConnection(lineSource->GetOutputPort());

        actor->SetMapper(mapper);
        actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
        actor->GetProperty()->SetLineWidth(3.0);

        // Add the actor to the scene
        renderer->AddActor(actor);
    }

    void Draw_Ellipsoid(double a, double b, double c, string color, int thickness)
    {
        // Generate the points on the surface of the ellipsoid
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

        // Set the number of points to generate along the major and minor axes
        const int num_points_major = 20;
        const int num_points_minor = 10;

        // Generate the points along the major axis
        for (int i = 0; i < num_points_major; i++)
        {
            double theta = 2.0 * vtkMath::Pi() * static_cast<double>(i) / static_cast<double>(num_points_major - 1);
            for (int j = 0; j < num_points_minor; j++)
            {
                double phi = vtkMath::Pi() * static_cast<double>(j) / static_cast<double>(num_points_minor - 1);
                double x = a * cos(theta) * sin(phi);
                double y = b * sin(theta) * sin(phi);
                double z = c * cos(phi);
                points->InsertNextPoint(x, y, z);
            }
        }

        // Generate the points along the minor axis
        for (int j = 0; j < num_points_minor; j++)
        {
            double phi = vtkMath::Pi() * static_cast<double>(j) / static_cast<double>(num_points_minor - 1);
            for (int i = 0; i < num_points_major; i++)
            {
                double theta = 2.0 * vtkMath::Pi() * static_cast<double>(i) / static_cast<double>(num_points_major - 1);
                double x = a * cos(theta) * sin(phi);
                double y = b * sin(theta) * sin(phi);
                double z = c * cos(phi);
                points->InsertNextPoint(x, y, z);
            }
        }

        // Set the points as the input data for the line source
        Ellipsoid_Source->SetPoints(points);

        // Generate the lines by connecting the points
        //Ellipsoid_Source->Update();

        // Create a mapper and actor to display the lines
        Ellipsoid_mapper->SetInputConnection(Ellipsoid_Source->GetOutputPort());
        Ellipsoid_mapper->Update();
        Ellipsoid_actor->SetMapper(Ellipsoid_mapper);
        set_color_and_thickness(color, thickness, Ellipsoid_actor);

        // Add the actor to the renderer
        renderer->AddActor(Ellipsoid_actor);
    }

    void DrawPolyLine(vtkSmartPointer<vtkPoints> points) {
        PolyLine_Source->SetPoints(points);
        PolyLine_mapper->SetInputConnection(PolyLine_Source->GetOutputPort());
        PolyLine_mapper->Update();
        PolyLine_actor->SetMapper(PolyLine_mapper);
        PolyLine_actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
        PolyLine_actor->GetProperty()->SetLineWidth(3.0);

        // Add the actor to the scene
        //renderer->RemoveAllViewProps();
        renderer->AddActor(PolyLine_actor);
    }

    void DeleteLine_Poly(vtkSmartPointer<vtkPoints> points) {
        DellineSource->SetPoint1(points->GetPoint(points->GetNumberOfPoints() - 2));
        DellineSource->SetPoint2(points->GetPoint(points->GetNumberOfPoints() - 1));

        // Create a mapper and actor for the line

        Delmapper->SetInputConnection(DellineSource->GetOutputPort());

        Delactor->SetMapper(Delmapper);
        Delactor->GetProperty()->SetColor(renderer->GetBackground());
        Delactor->GetProperty()->SetLineWidth(3.0);

        // Add the actor to the scene
        renderer->AddActor(Delactor);
    }

    void DrawPolygon(vtkSmartPointer<vtkPoints> points) {
        points->InsertNextPoint(points->GetPoint(0));
        Polygon_Source->SetPoints(points);
        Polygon_mapper->SetInputConnection(Polygon_Source->GetOutputPort());
        Polygon_mapper->Update();
        Polygon_actor->SetMapper(Polygon_mapper);
        Polygon_actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
        Polygon_actor->GetProperty()->SetLineWidth(3.0);

        // Add the actor to the scene
        //renderer->RemoveAllViewProps();
        renderer->AddActor(Polygon_actor);
    }

    string specify_color(double* color) {
        // Get the name of the color based on its RGB value
        if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 0.0) {
            return "Red";
        }
        else if (color[0] == 0.0 && color[1] == 1.0 && color[2] == 0.0) {
            return "Green";
        }
        else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 1.0) {
            return "Blue";
        }
        else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
            return "Yellow";
        }
        else if (color[0] == 1.0 && color[1] == 0.0 && color[2] == 1.0) {
            return "Magenta";
        }
        else if (color[0] == 0.0 && color[1] == 0.0 && color[2] == 0.0) {
            return "Black";
        }
        else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 1.0) {
            return "White";
        }
        else {
            return "Unknown";
        }
    }

    void Save() {
        // Access the first element in the set and convert it to a std::string
        std::string shape_name = drawnShapes_all.begin()->toStdString();

        // Ask user for TXT or CSV
        QMessageBox messageBox;
        messageBox.setText("Choose Save Type");
        QAbstractButton* txtButton = messageBox.addButton(QMessageBox::tr("TXT"), QMessageBox::YesRole);
        QAbstractButton* csvButton = messageBox.addButton(QMessageBox::tr("CSV"), QMessageBox::YesRole);
        messageBox.exec();
        QString buttonText = messageBox.clickedButton()->text();
        std::string mode = buttonText.toStdString();

        QString filename_txt;
        QString filename_csv;
        if (mode == "TXT") {
            filename_txt = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text files (*.txt)");
        }
        else {
            filename_csv = QFileDialog::getSaveFileName(nullptr, "Save File", "", "CSV files (*.csv)");
        }

        if (mode == "TXT") {
            if (!filename_txt.isEmpty()) {
                // Open the TXT output file for writing
                std::ofstream outputFile_txt(filename_txt.toStdString());
                outputFile_txt << "Shape\t\tX1\tY1\tX2\tY2\tSemi-axis-X\tSemi-axis-Y\tSemi-axis-Z\tCenter X\tCenter Y\tCenter Z\t\tRadius\t\tMajor Axis\tMinor Axis\tHeight\tNumber of sides\tColor\tThickness\tDeleted\t2D/3D" << std::endl;
                for (const auto& shape : drawnShapes_all) {
                    if (shape == "Circle") {
                        // Get the properties of the circle
                        double* color = actor_circle->GetProperty()->GetColor();
                        double thickness = actor_circle->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || circle_deleted == true) {
                            if (circle_mouse_enter == true) {
                                outputFile_txt << "Circle\t\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << center_x_circle << "\t" << center_y_circle << "\t" << "NULL" << "\t\t\t" << Radius_Circle << "\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes" << "\t" << "2D" << std::endl;
                            }
                            else {
                                outputFile_txt << "Circle\t\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0" << "\t\t" << "0" << "\t\t" << "NULL" << "\t\t\t" << Radius_Circle << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes" << "\t" << "2D" << std::endl;
                            }
                        }
                        else {
                            if (circle_mouse_enter == true) {
                                outputFile_txt << "Circle\t\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << center_x_circle << "\t" << center_y_circle << "\t" << "NULL" << "\t\t\t" << Radius_Circle << "\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "No" << "\t" << "2D" << std::endl;
                            }
                            else {
                                outputFile_txt << "Circle\t\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0" << "\t\t" << "0" << "\t\t" << "NULL" << "\t\t\t" << Radius_Circle << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "No" << "\t" << "2D" << std::endl;
                            }
                        }
                    }
                    else if (shape == "Star") {
                        //Get the color and thickness 
                        double* color = actor_Star->GetProperty()->GetColor();
                        double thickness = actor_Star->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Star_deleted == true) {
                            outputFile_txt << "Star\t\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "NULL\t\t\t" << Radius_Star << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "2D" << std::endl;
                        }
                        else {
                            outputFile_txt << "Star\t\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "NULL\t\t\t" << Radius_Star << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "No\t" << "2D" << std::endl;
                        }
                    }
                    else if (shape == "Ellipse") {
                        //Get the color and thickness of the Ellipse
                        double* color = actor_Ellipse->GetProperty()->GetColor();
                        double thickness = actor_Ellipse->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || ellipse_deleted == true) {
                            if (ellipse_mouse_enter == true) {
                                outputFile_txt << "Ellipse\t\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << center_x_ellipse << "\t" << center_y_ellipse << "\t" << "NULL" << "\t\t\t" << "NULL\t\t" << MAJOR_AXIS << "\t" << MINOR_AXIS << "\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes" << "\t" << "2D" << std::endl;
                            }
                            else {
                                outputFile_txt << "Ellipse\t\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0" << "\t\t" << "0" << "\t\t" << "NULL" << "\t\t\t" << "NULL" << "\t\t" << MAJOR_AXIS << "\t\t" << MINOR_AXIS << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "2D" << std::endl;
                            }
                        }
                        else {
                            if (ellipse_mouse_enter == true) {
                                outputFile_txt << "Ellipse\t\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << center_x_ellipse << "\t" << center_y_ellipse << "\t" << "NULL" << "\t\t\t" << "NULL\t\t" << MAJOR_AXIS << "\t" << MINOR_AXIS << "\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "No" << "\t" << "2D" << std::endl;
                            }
                            else {
                                outputFile_txt << "Ellipse\t\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0" << "\t\t" << "0" << "\t\t" << "NULL" << "\t\t\t" << "NULL" << "\t\t" << MAJOR_AXIS << "\t\t" << MINOR_AXIS << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "No\t" << "2D" << std::endl;
                            }
                        }
                    }
                    else if (shape == "Cylinder") {
                        //Get the color and thickness of the Cylinder
                        double* color = actor_Cylinder->GetProperty()->GetColor();
                        double thickness = actor_Cylinder->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Cylinder_deleted == true) {
                            outputFile_txt << "Cylinder\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "0\t\t\t" << Radius_Cylinder << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << Height_Cylinder << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "3D" << std::endl;
                        }
                        else {
                            outputFile_txt << "Cylinder\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "0\t\t\t" << Radius_Cylinder << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << Height_Cylinder << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "No\t" << "3D" << std::endl;
                        }
                    }
                    else if (shape == "Regular Polygon") {
                        //Get the color and thickness of the Regular Polygon
                        double* color = actor_Regular_Polygon->GetProperty()->GetColor();
                        double thickness = actor_Regular_Polygon->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Regular_Polygon_deleted == true) {
                            outputFile_txt << "Regular_Polygon\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "NULL\t\t\t" << Radius_Reg_Polygon << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << NO_POINTS << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "2D" << std::endl;
                        }
                        else {
                            outputFile_txt << "Regular_Polygon\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "NULL\t\t\t" << Radius_Reg_Polygon << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << NO_POINTS << "\t\t" << color_name << "\t" << thickness << "\t\t" << "No\t" << "2D" << std::endl;
                        }
                    }
                    else if (shape == "Square") {
                        //Get the color and thickness of the Square
                        double* color = actor_Square->GetProperty()->GetColor();
                        double thickness = actor_Square->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Square_deleted == true) {
                            outputFile_txt << "Square\t\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "NULL\t\t\t" << Radius_Square << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "2D" << std::endl;
                        }
                        else {
                            outputFile_txt << "Square\t\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "NULL\t\t\t" << Radius_Square << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "No\t" << "2D" << std::endl;
                        }
                    }
                    else if (shape == "Hexahedron") {
                        //Get the color and thickness of the Hexahedron
                        double* color = actor_Hexahedron->GetProperty()->GetColor();
                        double thickness = actor_Hexahedron->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Hexahedron_deleted == true) {
                            outputFile_txt << "Hexahedron\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "0\t\t\t" << Radius_Hexahedron << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes" << "\t" << "3D" << std::endl;
                        }
                        else {
                            outputFile_txt << "Hexahedron\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "0\t\t\t" << Radius_Hexahedron << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "No" << "\t" << "3D" << std::endl;
                        }
                    }
                    else if (shape == "Arc") {
                        //Get the color and thickness of the Arc
                        double* color = actor_Arc->GetProperty()->GetColor();
                        double thickness = actor_Arc->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Arc_deleted == true) {
                            if (arc_mouse_enter == true) {
                                outputFile_txt << "Arc\t\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << center_x_arc << "\t" << center_y_arc << "\t" << "NULL\t\t\t" << Radius_Arc << "\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "2D" << std::endl;
                            }
                            else {
                                outputFile_txt << "Arc\t\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "NULL\t\t\t" << Radius_Arc << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "2D" << std::endl;
                            }
                        }
                        else {
                            if (arc_mouse_enter == true) {
                                outputFile_txt << "Arc\t\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << center_x_arc << "\t" << center_y_arc << "\t" << "NULL\t\t\t" << Radius_Arc << "\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "NO\t" << "2D" << std::endl;
                            }
                            else {
                                outputFile_txt << "Arc\t\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "NULL\t\t\t" << Radius_Arc << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "NO\t" << "2D" << std::endl;
                            }
                        }
                    }
                    else if (shape == "Sphere") {
                        //Get the color and thickness of the Sphere
                        double* color = actor_Football->GetProperty()->GetColor();
                        double thickness = actor_Football->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Sphere_deleted == true) {
                            if (sphere_mouse_enter == true) {
                                outputFile_txt << "Sphere\t\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << center_x_sphere << "\t" << center_y_sphere << "\t" << center_z_sphere << "\t\t" << Radius_Sphere << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "3D" << std::endl;
                            }
                            else {
                                outputFile_txt << "Sphere\t\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "0\t\t\t" << Radius_Sphere << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "3D" << std::endl;
                            }
                        }
                        else {
                            if (sphere_mouse_enter == true) {
                                outputFile_txt << "Sphere\t\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL" << "\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << center_x_sphere << "\t" << center_y_sphere << "\t" << center_z_sphere << "\t\t" << Radius_Sphere << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "No\t" << "3D" << std::endl;
                            }
                            else {
                                outputFile_txt << "Sphere\t\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "0\t\t" << "0\t\t" << "0\t\t\t" << Radius_Sphere << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t\t" << "NULL" << "\t" << "NULL" << "\t\t" << color_name << "\t" << thickness << "\t\t" << "No\t" << "3D" << std::endl;
                            }
                        }
                    }
                    else if (shape == "Line") {
                        double* color = actor->GetProperty()->GetColor();
                        double thickness = actor->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || line_deleted == true) {
                            outputFile_txt << "Line\t\t" << x1_line << "\t" << y1_line << "\t" << x2_line << "\t" << y2_line << "\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << (x2_line + x1_line) / 2 << "\t\t" << (y2_line + y1_line) / 2 << "\t\t" << "NULL\t\t\t" << "NULL\t\t" << "NULL" << "\t\t" << "NULL\t\t" << "NULL\t" << "NULL\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "2D" << std::endl;
                        }
                        else {
                            outputFile_txt << "Line\t\t" << x1_line << "\t" << y1_line << "\t" << x2_line << "\t" << y2_line << "\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << (x2_line + x1_line) / 2 << "\t\t" << (y2_line + y1_line) / 2 << "\t\t" << "NULL\t\t\t" << "NULL\t\t" << "NULL" << "\t\t" << "NULL\t\t" << "NULL\t" << "NULL\t\t" << color_name << "\t" << thickness << "\t\t" << "No\t" << "2D" << std::endl;
                        }
                    }
                    else if (shape == "Ellipsoid") {
                        //Get the color and thickness of the Sphere
                        double* color = Ellipsoid_actor->GetProperty()->GetColor();
                        double thickness = Ellipsoid_actor->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Ellipsoid_deleted == true) {
                            outputFile_txt << "Ellipsoid\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << semi_axis_x << "\t\t" << semi_axis_y << "\t\t" << semi_axis_z << "\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t" << "NULL\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "3D" << std::endl;
                        }
                        else {
                            outputFile_txt << "Ellipsoid\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << semi_axis_x << "\t\t" << semi_axis_y << "\t\t" << semi_axis_z << "\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t" << "NULL\t\t" << color_name << "\t" << thickness << "\t\t" << "NO\t" << "3D" << std::endl;
                        }
                    }
                    else if (shape == "Polyline") {
                        //Get the color and thickness of the Sphere
                        double* color = PolyLine_actor->GetProperty()->GetColor();
                        double thickness = PolyLine_actor->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || polyline_deleted == true) {
                            outputFile_txt << "Polyline\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t" << NO_POINTS_polyline - 1 << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "2D";
                        }
                        else {
                            outputFile_txt << "Polyline\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t" << NO_POINTS_polyline - 1 << "\t\t" << color_name << "\t" << thickness << "\t\t" << "NO\t" << "2D";
                        }
                    }
                    else if (shape == "Polygon") {
                        //Get the color and thickness of the Sphere
                        double* color = Polygon_actor->GetProperty()->GetColor();
                        double thickness = Polygon_actor->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Polygon_deleted == true) {
                            outputFile_txt << "Polygon\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t" << NO_POINTS_polygon << "\t\t" << color_name << "\t" << thickness << "\t\t" << "Yes\t" << "2D";
                        }
                        else {
                            outputFile_txt << "Polygon\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t\t" << "NULL\t" << NO_POINTS_polygon << "\t\t" << color_name << "\t" << thickness << "\t\t" << "NO\t" << "2D";
                        }
                    }
                    else {
                        return;
                    }
                }
            }
        }
        else {
            if (!filename_csv.isEmpty()) {
                // Open the CSV output file for writing
                std::ofstream outputFile_csv(filename_csv.toStdString());
                outputFile_csv << "Shape,X1,Y1,X2,Y2,Semi-axis-X,Semi-axis-Y,Semi-axis-Z,Center X,Center Y, Center Z,Radius,Major Axis,Minor Axis,Height,Number of sides,Color,Thickness,Deleted,2D/3D" << std::endl;
                for (const auto& shape : drawnShapes_all) {
                    if (shape == "Circle") {
                        // Get the properties of the circle
                        double* color = actor_circle->GetProperty()->GetColor();
                        double thickness = actor_circle->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || circle_deleted == true) {
                            if (circle_mouse_enter == true) {
                                outputFile_csv << "Circle," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << center_x_circle << "," << center_y_circle << "," << "-," << Radius_Circle << "," << "-" << "," << "-" << "," << "-" << "," << "-" << "," << color_name << "," << thickness << "," << "Yes" << ",2D" << std::endl;
                            }
                            else {
                                outputFile_csv << "Circle," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0" << "," << "0" << "," << "-," << Radius_Circle << "," << "-" << "," << "-" << "," << "-" << "," << "-" << "," << color_name << "," << thickness << "," << "Yes" << ",2D" << std::endl;
                            }
                        }
                        else {
                            if (circle_mouse_enter == true) {
                                outputFile_csv << "Circle," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << center_x_circle << "," << center_y_circle << "," << "-," << Radius_Circle << "," << "-" << "," << "-" << "," << "-" << "," << "-" << "," << color_name << "," << thickness << "," << "No" << ",2D" << std::endl;
                            }
                            else {
                                outputFile_csv << "Circle," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0" << "," << "0" << "," << "-," << Radius_Circle << "," << "-" << "," << "-" << "," << "-" << "," << "-" << "," << color_name << "," << thickness << "," << "No" << ",2D" << std::endl;
                            }
                        }
                    }
                    else if (shape == "Square") {
                        //Get the color and thickness 
                        double* color = actor_Square->GetProperty()->GetColor();
                        double thickness = actor_Square->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Square_deleted == true) {
                            outputFile_csv << "Square," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "-," << Radius_Square << "," << "-" << "," << "-" << "," << "-" << "," << "-" << "," << color_name << "," << thickness << "," << "Yes," << "2D" << std::endl;
                        }
                        else {
                            outputFile_csv << "Square," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "-," << Radius_Square << "," << "-" << "," << "-" << "," << "-" << "," << "-" << "," << color_name << "," << thickness << "," << "Yes," << "2D" << std::endl;
                        }
                    }
                    else if (shape == "Star") {
                        //Get the color and thickness of the Star
                        double* color = actor_Star->GetProperty()->GetColor();
                        double thickness = actor_Star->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Star_deleted == true) {
                            outputFile_csv << "Star," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "-," << Radius_Star << "," << "-" << "," << "-" << "," << "-" << "," << "-" << "," << color_name << "," << thickness << "," << "Yes," << "2D" << std::endl;
                        }
                        else {
                            outputFile_csv << "Star," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "-," << Radius_Star << "," << "-" << "," << "-" << "," << "-" << "," << "-" << "," << color_name << "," << thickness << "," << "No," << "2D" << std::endl;
                        }
                    }
                    else if (shape == "Ellipse") {
                        //Get the color and thickness of the Ellipse
                        double* color = actor_Ellipse->GetProperty()->GetColor();
                        double thickness = actor_Ellipse->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || ellipse_deleted == true) {
                            if (ellipse_mouse_enter == true) {
                                outputFile_csv << "Ellipse," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << center_x_ellipse << "," << center_y_ellipse << "," << "-," << "-," << MAJOR_AXIS << "," << MINOR_AXIS << "," << "-," << "-," << color_name << "," << thickness << "," << "Yes," << "2D" << std::endl;
                            }
                            else {
                                outputFile_csv << "Ellipse," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "-," << "-," << MAJOR_AXIS << "," << MINOR_AXIS << "," << "-," << "-," << color_name << "," << thickness << "," << "Yes," << "2D" << std::endl;
                            }
                        }
                        else {
                            if (ellipse_mouse_enter == true) {
                                outputFile_csv << "Ellipse," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << center_x_ellipse << "," << center_y_ellipse << "," << "-," << "-," << MAJOR_AXIS << "," << MINOR_AXIS << "," << "-," << "-," << color_name << "," << thickness << "," << "No," << "2D" << std::endl;
                            }
                            else {
                                outputFile_csv << "Ellipse," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "-," << "-," << MAJOR_AXIS << "," << MINOR_AXIS << "," << "-," << "-," << color_name << "," << thickness << "," << "No," << "2D" << std::endl;
                            }
                        }
                    }
                    else if (shape == "Cylinder") {
                        //Get the color and thickness of the Cylinder
                        double* color = actor_Cylinder->GetProperty()->GetColor();
                        double thickness = actor_Cylinder->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Cylinder_deleted == true) {
                            outputFile_csv << "Cylinder," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "0," << Radius_Cylinder << "," << "-," << "-," << Height_Cylinder << "," << "-," << color_name << "," << thickness << "," << "Yes," << "3D" << std::endl;
                        }
                        else {
                            outputFile_csv << "Cylinder," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "0," << Radius_Cylinder << "," << "-," << "-," << Height_Cylinder << "," << "-," << color_name << "," << thickness << "," << "No," << "3D" << std::endl;
                        }
                    }
                    else if (shape == "Regular Polygon") {
                        //Get the color and thickness of the Regular Polygon
                        double* color = actor_Regular_Polygon->GetProperty()->GetColor();
                        double thickness = actor_Regular_Polygon->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Regular_Polygon_deleted == true) {
                            outputFile_csv << "Regular Polygon," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "-," << Radius_Reg_Polygon << "," << "-" << "," << "-" << "," << "-" << "," << NO_POINTS << "," << color_name << "," << thickness << "," << "Yes," << "2D" << std::endl;
                        }
                        else {
                            outputFile_csv << "Regular Polygon," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "-," << Radius_Reg_Polygon << "," << "-" << "," << "-" << "," << "-" << "," << NO_POINTS << "," << color_name << "," << thickness << "," << "No," << "2D" << std::endl;
                        }
                    }
                    else if (shape == "Hexahedron") {
                        //Get the color and thickness of the Hexahedron
                        double* color = actor_Hexahedron->GetProperty()->GetColor();
                        double thickness = actor_Hexahedron->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Hexahedron_deleted == true) {
                            outputFile_csv << "Hexahedron," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "0," << Radius_Hexahedron << "," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "Yes," << "3D" << std::endl;
                        }
                        else {
                            outputFile_csv << "Hexahedron," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "0," << Radius_Hexahedron << "," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "No," << "3D" << std::endl;
                        }
                    }
                    else if (shape == "Arc") {
                        //Get the color and thickness of the Arc
                        double* color = actor_Arc->GetProperty()->GetColor();
                        double thickness = actor_Arc->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Arc_deleted == true) {
                            if (arc_mouse_enter == true) {
                                outputFile_csv << "Arc," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << center_x_arc << "," << center_y_arc << "," << "-," << Radius_Arc << "," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "Yes," << "2D" << std::endl;
                            }
                            else {
                                outputFile_csv << "Arc," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "-," << Radius_Arc << "," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "Yes," << "2D" << std::endl;
                            }
                        }
                        else {
                            if (arc_mouse_enter == true) {
                                outputFile_csv << "Arc," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << center_x_arc << "," << center_y_arc << "," << "-," << Radius_Arc << "," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "No," << "2D" << std::endl;
                            }
                            else {
                                outputFile_csv << "Arc," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "-," << Radius_Arc << "," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "No," << "2D" << std::endl;
                            }
                        }
                    }
                    else if (shape == "Sphere") {
                        //Get the color and thickness of the Sphere
                        double* color = actor_Football->GetProperty()->GetColor();
                        double thickness = actor_Football->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Sphere_deleted == true) {
                            if (sphere_mouse_enter == true) {
                                outputFile_csv << "Sphere," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << center_x_sphere << "," << center_y_sphere << "," << center_z_sphere << "," << Radius_Sphere << "," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "Yes," << "3D" << std::endl;
                            }
                            else {
                                outputFile_csv << "Sphere," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "0," << Radius_Sphere << "," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "Yes," << "3D" << std::endl;
                            }
                        }
                        else {
                            if (sphere_mouse_enter == true) {
                                outputFile_csv << "Sphere," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << center_x_sphere << "," << center_y_sphere << "," << center_z_sphere << "," << Radius_Sphere << "," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "No," << "3D" << std::endl;
                            }
                            else {
                                outputFile_csv << "Sphere," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "0," << "0," << "0," << Radius_Sphere << "," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "No," << "3D" << std::endl;
                            }
                        }
                    }
                    else if (shape == "Line") {
                        //Get the color and thickness of the Line
                        double* color = actor->GetProperty()->GetColor();
                        double thickness = actor->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || line_deleted == true) {
                            outputFile_csv << "Line," << x1_line << "," << y1_line << "," << x2_line << "," << y2_line << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "Yes," << "2D" << std::endl;
                        }
                        else {
                            outputFile_csv << "Line," << x1_line << "," << y1_line << "," << x2_line << "," << y2_line << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "No," << "2D" << std::endl;
                        }
                    }
                    else if (shape == "Ellipsoid") {
                        //Get the color and thickness of the Ellipsoid
                        double* color = Ellipsoid_actor->GetProperty()->GetColor();
                        double thickness = Ellipsoid_actor->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Ellipsoid_deleted == true) {
                            outputFile_csv << "Ellipsoid," << "-," << "-," << "-," << "-," << semi_axis_x << "," << semi_axis_y << "," << semi_axis_z << "," << "0," << "0," << "0," << "-," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "Yes," << "3D" << std::endl;
                        }
                        else {
                            outputFile_csv << "Ellipsoid," << "-," << "-," << "-," << "-," << semi_axis_x << "," << semi_axis_y << "," << semi_axis_z << "," << "0," << "0," << "0," << "-," << "-," << "-," << "-," << "-," << color_name << "," << thickness << "," << "No," << "3D" << std::endl;
                        }
                    }
                    else if (shape == "Polyline") {
                        double* color = PolyLine_actor->GetProperty()->GetColor();
                        double thickness = PolyLine_actor->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || polyline_deleted == true) {
                            outputFile_csv << "Polyline," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << NO_POINTS_polyline - 1 << "," << color << "," << thickness << ",Yes," << "2D";
                        }
                        else {
                            outputFile_csv << "Polyline," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << NO_POINTS_polyline - 1 << "," << color << "," << thickness << ",NO," << "2D";
                        }
                    }
                    else if (shape == "Polygon") {
                        //Get the color and thickness of the Ellipsoid
                        double* color = Polygon_actor->GetProperty()->GetColor();
                        double thickness = Polygon_actor->GetProperty()->GetLineWidth();
                        string color_name = specify_color(color);
                        if (drawnShapes.size() == 0 || Polygon_deleted == true) {
                            outputFile_csv << "Polygon," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << NO_POINTS_polygon << "," << color << "," << thickness << ",Yes," << "2D";
                        }
                        else {
                            outputFile_csv << "Polygon," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << "-," << NO_POINTS_polygon << "," << color << "," << thickness << ",NO," << "2D";
                        }
                    }
                    else {
                        return;
                    }
                }
            }
        }
    }

    void Change_Color(string color_name, vtkSmartPointer<vtkActor> temp_actor) {
        if (color_name == "Red")
        {
            temp_actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
        }
        else if (color_name == "Green")
        {
            temp_actor->GetProperty()->SetColor(0.0, 1.0, 0.0);
        }
        else if (color_name == "Blue")
        {
            temp_actor->GetProperty()->SetColor(0.0, 0.0, 1.0);
        }
        else if (color_name == "Yellow")
        {
            temp_actor->GetProperty()->SetColor(1.0, 1.0, 0.0);
        }
        else if (color_name == "Magenta")
        {
            temp_actor->GetProperty()->SetColor(1.0, 0.0, 1.0);
        }
        else if (color_name == "Black")
        {
            temp_actor->GetProperty()->SetColor(0.0, 0.0, 0.0);
        }
        else if (color_name == "White")
        {
            temp_actor->GetProperty()->SetColor(1.0, 1.0, 1.0);
        }
    }

    void ChangeColor_Button(QComboBox* comboBox_Color, vtkGenericOpenGLRenderWindow* window, QComboBox* comboBox_Shapes) {
        QString color_name = comboBox_Color->currentText();
        QString shape_name = comboBox_Shapes->currentText();
        std::string color_name_std = color_name.toStdString(); // Convert QString to std::string
        vtkNew<MouseInteractorStyleDrawLine> style;
        //style->setShapeName(shape_name);
        style->setDrawFlag(false);
        vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
        renderWindowInteractor->SetRenderWindow(window);

        style->SetRenderer(renderer);

        renderWindowInteractor->SetInteractorStyle(style.Get());
        if (count_shapes > 1) {
            QMessageBox messageBox;
            messageBox.setText("Choose which shape you want to color");
            messageBox.addButton(QMessageBox::tr("Last shape drawn"), QMessageBox::YesRole);
            messageBox.addButton(QMessageBox::tr("All the Shapes"), QMessageBox::YesRole);
            messageBox.addButton(QMessageBox::tr("Specific shape"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            color_mode = buttonText.toStdString();
            if (color_mode == "Last shape drawn") {
                if (shape_name == "Circle") {
                    Change_Color(color_name_std, actor_circle);
                }
                else if (shape_name == "Line") {
                    Change_Color(color_name_std, actor);
                }
                else if (shape_name == "Ellipse") {
                    Change_Color(color_name_std, actor_Ellipse);
                }
                else if (shape_name == "Arc") {
                    Change_Color(color_name_std, actor_Arc);
                }
                else if (shape_name == "Sphere") {
                    Change_Color(color_name_std, actor_Football);
                }
                else if (shape_name == "Hexahedron") {
                    Change_Color(color_name_std, actor_Hexahedron);
                }
                else if (shape_name == "Regular Polygon") {
                    Change_Color(color_name_std, actor_Regular_Polygon);
                }
                else if (shape_name == "Cylinder") {
                    Change_Color(color_name_std, actor_Cylinder);
                }
                else if (shape_name == "Square") {
                    Change_Color(color_name_std, actor_Square);
                }
                else if (shape_name == "Star") {
                    Change_Color(color_name_std, actor_Star);
                }
                else if (shape_name == "Polyline") {
                    Change_Color(color_name_std, PolyLine_actor);
                }
                else if (shape_name == "Polygon") {
                    Change_Color(color_name_std, Polygon_actor);
                }
                else if (shape_name == "Ellipsoid") {
                    Change_Color(color_name_std, Ellipsoid_actor);
                }
                else {
                    return;
                }
            }
            else if (color_mode == "All the Shapes") {
                vtkActorCollection* actors = renderer->GetActors(); // Get the collection of actors in the renderer
                actors->InitTraversal(); // Initialize the actors traversal

                vtkActor* actor_all = nullptr;
                while ((actor_all = actors->GetNextActor()) != nullptr) {
                    Change_Color(color_name_std, actor_all);
                }
            }
            else if (color_mode == "Specific shape") {
                QMessageBox messageBox_edit;
                QComboBox* comboBox = new QComboBox(); // Create a new QComboBox object
                for (const auto& shapeName : drawnShapes) {
                    std::cout << shapeName.toStdString() << " ";
                    comboBox->addItem(shapeName);
                }
                messageBox_edit.layout()->addWidget(comboBox); // Add the QComboBox to the QMessageBox's layout
                messageBox_edit.exec(); // Show the QMessageBox
                QString selectedShape = comboBox->currentText(); // Get the currently selected shape from the QComboBox
                if (selectedShape.toStdString() == "Circle") {
                    Change_Color(color_name_std, actor_circle);
                }
                else if (selectedShape.toStdString() == "Line") {
                    Change_Color(color_name_std, actor);
                }
                else if (selectedShape.toStdString() == "Ellipse") {
                    Change_Color(color_name_std, actor_Ellipse);
                }
                else if (selectedShape.toStdString() == "Arc") {
                    Change_Color(color_name_std, actor_Arc);
                }
                else if (selectedShape.toStdString() == "Sphere") {
                    Change_Color(color_name_std, actor_Football);
                }
                else if (selectedShape.toStdString() == "Hexahedron") {
                    Change_Color(color_name_std, actor_Hexahedron);
                }
                else if (selectedShape.toStdString() == "Regular Polygon") {
                    Change_Color(color_name_std, actor_Regular_Polygon);
                }
                else if (selectedShape.toStdString() == "Cylinder") {
                    Change_Color(color_name_std, actor_Cylinder);
                }
                else if (selectedShape.toStdString() == "Square") {
                    Change_Color(color_name_std, actor_Square);
                }
                else if (selectedShape.toStdString() == "Star") {
                    Change_Color(color_name_std, actor_Star);
                }
                else if (selectedShape.toStdString() == "Polyline") {
                    Change_Color(color_name_std, PolyLine_actor);
                }
                else if (selectedShape.toStdString() == "Polygon") {
                    Change_Color(color_name_std, Polygon_actor);
                }
                else if (selectedShape.toStdString() == "Ellipsoid") {
                    Change_Color(color_name_std, Ellipsoid_actor);
                }
                else {
                    return;
                }
            }
            else {
                return;
            }
        }
        else {
            if (shape_name == "Circle") {
                Change_Color(color_name_std, actor_circle);
            }
            else if (shape_name == "Line") {
                Change_Color(color_name_std, actor);
            }
            else if (shape_name == "Ellipse") {
                Change_Color(color_name_std, actor_Ellipse);
            }
            else if (shape_name == "Arc") {
                Change_Color(color_name_std, actor_Arc);
            }
            else if (shape_name == "Sphere") {
                Change_Color(color_name_std, actor_Football);
            }
            else if (shape_name == "Hexahedron") {
                Change_Color(color_name_std, actor_Hexahedron);
            }
            else if (shape_name == "Regular Polygon") {
                Change_Color(color_name_std, actor_Regular_Polygon);
            }
            else if (shape_name == "Cylinder") {
                Change_Color(color_name_std, actor_Cylinder);
            }
            else if (shape_name == "Square") {
                Change_Color(color_name_std, actor_Square);
            }
            else if (shape_name == "Star") {
                Change_Color(color_name_std, actor_Star);
            }
            else if (shape_name == "Polyline") {
                Change_Color(color_name_std, PolyLine_actor);
            }
            else if (shape_name == "Polygon") {
                Change_Color(color_name_std, Polygon_actor);
            }
            else if (shape_name == "Ellipsoid") {
                Change_Color(color_name_std, Ellipsoid_actor);
            }
            else {
                return;
            }
        }
        window->Render();
    }

    void drawnshapes_and_all_count(string shape_name) {
        // Convert shape_name from string to QString
        QString qShapeName = QString::fromStdString(shape_name);

        drawnShapes.insert(qShapeName);
        drawnShapes_all.insert(qShapeName);
        count_shapes++;
    }

    void Load(QComboBox* comboBox)
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

                //// Read the second line (data)
                //std::getline(inputFile, line);
                //std::istringstream iss(line);
                //std::string shape;
                // Read the data lines
                while (std::getline(inputFile, line)) {
                    std::istringstream iss(line);
                    std::string shape;

                    double radius;
                    double cylinder_height{};
                    double major_axis{};
                    double minor_axis{};
                    double center_x, center_y, center_z;
                    double x1, y1, x2, y2; //// For Line
                    double zeros;
                    double a, b, c;
                    int no_of_sides;
                    std::string color_name, is_deleted, check_blank;;
                    double thickness;
                    iss >> shape;
                    if (shape == "Circle") {  
                        iss >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> radius >> check_blank >> check_blank >> check_blank >> check_blank >> color_name >> thickness >> is_deleted >> check_blank;
                        if (is_deleted == "No") {
                            Draw_circle(radius, color_name, thickness, 0, 0);
                            drawnshapes_and_all_count(shape);
                            comboBox->setCurrentText("Circle");
                        }
                        else {
                            return;
                        }
                    }
                    else if (shape == "Sphere") {  
                        iss >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> center_x >> center_y >> center_z >> radius >> check_blank >> check_blank >> check_blank >> check_blank >> color_name >> thickness >> is_deleted >> check_blank;
                        if (is_deleted == "No") {
                            Draw_Sphere(radius, color_name, thickness, center_x, center_y, center_z);
                            drawnshapes_and_all_count(shape);
                            comboBox->setCurrentText("Sphere");
                        }
                        else {
                            return;
                        }
                    }
                    else if (shape == "Arc") {
                        iss >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> center_x >> center_y >> check_blank >> radius >> check_blank >> check_blank >> check_blank >> check_blank >> color_name >> thickness >> is_deleted >> check_blank;
                        if (is_deleted == "No") {
                            Draw_Arc(radius, color_name, thickness, center_x, center_y, 1.0, vtkMath::Pi());
                            drawnshapes_and_all_count(shape);
                            comboBox->setCurrentText("Arc");
                        }
                        else {
                            return;
                        }
                    }///////////////////////////////////////
                    else if (shape == "Hexahedron") {  
                        iss >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> radius >> check_blank >> check_blank >> check_blank >> check_blank >> color_name >> thickness >> is_deleted >> check_blank;
                        if (is_deleted == "No") {
                            Draw_Hexahedron(radius, color_name, thickness);
                            drawnshapes_and_all_count(shape);
                            comboBox->setCurrentText("Hexahedron");
                        }
                        else {
                            return;
                        }
                    }
                    else if (shape == "Regular_Polygon") {   
                        iss >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> radius >> check_blank >> check_blank >> check_blank >> no_of_sides >> color_name >> thickness >> is_deleted >> check_blank;
                        if (is_deleted == "No") {
                            Draw_Regular_Polygon(radius, no_of_sides, color_name, thickness);
                            drawnshapes_and_all_count(shape);
                            comboBox->setCurrentText("Regular_Polygon");
                        }
                        else {
                            return;
                        }
                    }
                    else if (shape == "Square") { ////////////////////
                        iss >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> radius >> check_blank >> check_blank >> check_blank >> check_blank >> color_name >> thickness >> is_deleted >> check_blank;
                        if (is_deleted == "No") {
                            Draw_Square(radius, color_name, thickness);
                            drawnshapes_and_all_count(shape);
                            comboBox->setCurrentText("Square");
                        }
                        else {
                            return;
                        }
                    }
                    else if (shape == "Cylinder") {  /////working
                        iss >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> radius >> check_blank >> check_blank >> cylinder_height >> check_blank >> color_name >> thickness >> is_deleted >> check_blank;
                        if (is_deleted == "No") {
                            Draw_Cylinder(radius, cylinder_height, color_name, thickness);
                            drawnshapes_and_all_count(shape);
                            comboBox->setCurrentText("Cylinder");
                        }
                    }
                    else if (shape == "Ellipse") {   // working
                        iss >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> major_axis >> minor_axis >> check_blank >> check_blank >> color_name >> thickness >> is_deleted >> check_blank;
                        if (is_deleted == "No") {
                            Draw_Ellipse(major_axis, minor_axis, color_name, thickness, 0, 0);
                            drawnshapes_and_all_count(shape);
                            comboBox->setCurrentText("Ellipse");
                        }
                    }
                    else if (shape == "Star") {    // working
                        iss >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> radius >> check_blank >> check_blank >> check_blank >> check_blank >> color_name >> thickness >> is_deleted >> check_blank;
                        if (is_deleted == "No") {
                            Draw_Star(radius, color_name, thickness);
                            drawnshapes_and_all_count(shape);
                            comboBox->setCurrentText("Star");
                        }
                    }
                    else if (shape == "Line") {  // working
                        iss >> x1 >> y1 >> x2 >> y2 >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> color_name >> thickness >> is_deleted >> check_blank;
                        if (is_deleted == "No") {
                            Draw_Line(x1, y1, x2, y2, color_name, thickness);
                            drawnshapes_and_all_count(shape);
                            comboBox->setCurrentText("Line");
                        }
                        else {
                            return;
                        }
                    }
                    else if (shape == "Ellipsoid") {
                        iss >> check_blank >> check_blank >> check_blank >> check_blank >> a >> b >> c >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> check_blank >> color_name >> thickness >> is_deleted >> check_blank;
                        if (is_deleted == "No") {
                            Draw_Ellipsoid(a, b, c, color_name, thickness);
                            drawnshapes_and_all_count(shape);
                            comboBox->setCurrentText("Ellipsoid");
                        }
                        else {
                            return;
                        }
                    }
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
                    // Convert QString to string
                    std::string shapeStr = shape.toStdString();
                    if (shapeStr == "Circle") {
                        double radius = fields[11].toDouble();
                        std::string color_name = fields.value(16).toStdString();
                        double thickness = fields[17].toDouble();
                        std::string is_deleted = fields.value(18).toStdString();
                        if (is_deleted == "No") {
                            Draw_circle(radius, color_name, thickness, center_x_circle, center_y_circle);
                            drawnshapes_and_all_count(shapeStr);
                            comboBox->setCurrentText("Circle");
                        }
                    }
                    else if (shapeStr == "Sphere") {
                        double radius = fields[11].toDouble();
                        std::string color_name = fields.value(16).toStdString();
                        double thickness = fields[17].toDouble();
                        std::string is_deleted = fields.value(18).toStdString();
                        if (is_deleted == "No") {
                            Draw_Sphere(radius, color_name, thickness, center_x_sphere, center_x_sphere, center_z_sphere);
                            drawnshapes_and_all_count(shapeStr);
                            comboBox->setCurrentText("Sphere");
                        }
                    }
                    else if (shapeStr == "Arc") {
                        double radius = fields[11].toDouble();
                        std::string color_name = fields.value(16).toStdString();
                        double thickness = fields[17].toDouble();
                        std::string is_deleted = fields.value(18).toStdString();
                        if (is_deleted == "No") {
                            Draw_Arc(radius, color_name, thickness, center_x_arc, center_y_arc, 1.0, vtkMath::Pi());
                            drawnshapes_and_all_count(shapeStr);
                            comboBox->setCurrentText("Arc");
                        }
                    }
                    else if (shapeStr == "Hexahedron") {
                        double radius = fields[11].toDouble();
                        std::string color_name = fields.value(16).toStdString();
                        double thickness = fields[17].toDouble();
                        std::string is_deleted = fields.value(18).toStdString();
                        if (is_deleted == "No") {
                            Draw_Hexahedron(radius, color_name, thickness);
                            drawnshapes_and_all_count(shapeStr);
                            comboBox->setCurrentText("Hexahedron");
                        }
                    }
                    else if (shapeStr == "Regular Polygon") {
                        double radius = fields[11].toDouble();
                        int no_of_sides = fields[15].toInt();
                        std::string color_name = fields.value(16).toStdString();
                        double thickness = fields[17].toDouble();
                        std::string is_deleted = fields.value(18).toStdString();
                        if (is_deleted == "No") {
                            Draw_Regular_Polygon(radius, no_of_sides, color_name, thickness);
                            drawnshapes_and_all_count(shapeStr);
                            comboBox->setCurrentText("Regular Polygon");
                        }
                    }
                    else if (shapeStr == "Square") {
                        double radius = fields[11].toDouble();
                        std::string color_name = fields.value(16).toStdString();
                        double thickness = fields[17].toDouble();
                        std::string is_deleted = fields.value(18).toStdString();
                        if (is_deleted == "No") {
                            Draw_Square(radius, color_name, thickness);
                            drawnshapes_and_all_count(shapeStr);
                            comboBox->setCurrentText("Square");
                        }
                    }
                    else if (shapeStr == "Cylinder") {
                        double radius = fields[11].toDouble();
                        double cylinder_height = fields[14].toDouble();
                        std::string color_name = fields.value(16).toStdString();
                        double thickness = fields[17].toDouble();
                        std::string is_deleted = fields.value(18).toStdString();
                        if (is_deleted == "No") {
                            Draw_Cylinder(radius, cylinder_height, color_name, thickness);
                            drawnshapes_and_all_count(shapeStr);
                            comboBox->setCurrentText("Cylinder");
                        }
                    }
                    else if (shapeStr == "Ellipse") {
                        double major_axis = fields[12].toDouble();
                        double minor_axis = fields[13].toDouble();
                        std::string color_name = fields.value(16).toStdString();
                        double thickness = fields[17].toDouble();
                        std::string is_deleted = fields.value(18).toStdString();
                        if (is_deleted == "No") {
                            Draw_Ellipse(major_axis, minor_axis, color_name, thickness, center_x_ellipse, center_y_ellipse);
                            drawnshapes_and_all_count(shapeStr);
                            comboBox->setCurrentText("Ellipse");
                        }
                    }
                    else if (shapeStr == "Star") {
                        double radius = fields[11].toDouble();
                        std::string color_name = fields.value(16).toStdString();
                        double thickness = fields[17].toDouble();
                        std::string is_deleted = fields.value(18).toStdString();
                        if (is_deleted == "No") {
                            Draw_Star(radius, color_name, thickness);
                            drawnshapes_and_all_count(shapeStr);
                            comboBox->setCurrentText("Star");
                        }
                    }
                    else if (shapeStr == "Line") {
                        double x1 = fields[1].toDouble();
                        double y1 = fields[2].toDouble();
                        double x2 = fields[3].toDouble();
                        double y2 = fields[4].toDouble();
                        std::string color_name = fields.value(10).toStdString();
                        double thickness = fields[11].toDouble();
                        Draw_Line(x1, y1, x2, y2, color_name, thickness);
                    }
                    else if (shapeStr == "Ellipsoid") {
                        double a = fields[5].toDouble();
                        double b = fields[6].toDouble();
                        double c = fields[7].toDouble();
                        std::string color_name = fields.value(16).toStdString();
                        double thickness = fields[17].toDouble();
                        std::string is_deleted = fields.value(18).toStdString();
                        if (is_deleted == "No") {
                            Draw_Ellipsoid(a, b, c, color_name, thickness);
                            drawnshapes_and_all_count(shapeStr);
                            comboBox->setCurrentText("Ellipsoid");
                        }
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

    void updatethickness_2(vtkSmartPointer<vtkActor> tempactor, int thickness) {
        tempactor->GetProperty()->SetLineWidth(thickness);
        tempactor->GetMapper()->Update();
    }

    void UpdateThickness(int thickness, vtkGenericOpenGLRenderWindow* window, QComboBox* comboBox) {
        QString shape_name = comboBox->currentText();
        if (count_shapes > 1) {
            QMessageBox messageBox;
            messageBox.setText("Choose which shape you want to change the thickness");
            messageBox.addButton(QMessageBox::tr("Last shape drawn"), QMessageBox::YesRole);
            messageBox.addButton(QMessageBox::tr("All the Shapes"), QMessageBox::YesRole);
            messageBox.addButton(QMessageBox::tr("Specific shape"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            thickness_mode = buttonText.toStdString();
            vtkNew<MouseInteractorStyleDrawLine> style;
            //style->setShapeName(shape_name);
            style->setDrawFlag(false);
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            if (thickness_mode == "Last shape drawn") {
                if (shape_name == "Circle") {
                    updatethickness_2(actor_circle, thickness);
                }
                else if (shape_name == "Line") {
                    updatethickness_2(actor, thickness);
                }
                else if (shape_name == "Ellipse") {
                    updatethickness_2(actor_Ellipse, thickness);
                }
                else if (shape_name == "Arc") {
                    updatethickness_2(actor_Arc, thickness);
                }
                else if (shape_name == "Sphere") {
                    updatethickness_2(actor_Football, thickness);
                }
                else if (shape_name == "Hexahedron") {
                    updatethickness_2(actor_Hexahedron, thickness);
                }
                else if (shape_name == "Regular Polygon") {
                    updatethickness_2(actor_Regular_Polygon, thickness);
                }
                else if (shape_name == "Cylinder") {
                    updatethickness_2(actor_Cylinder, thickness);
                }
                else if (shape_name == "Square") {
                    updatethickness_2(actor_Square, thickness);
                }
                else if (shape_name == "Star") {
                    updatethickness_2(actor_Star, thickness);
                }
                else if (shape_name == "Polyline") {
                    updatethickness_2(PolyLine_actor, thickness);
                }
                else if (shape_name == "Polygon") {
                    updatethickness_2(Polygon_actor, thickness);
                }
                else if (shape_name == "Ellipsoid") {
                    updatethickness_2(Ellipsoid_actor, thickness);
                }
                else {
                    return;
                }
            }
            else if (thickness_mode == "All the Shapes") {
                vtkActorCollection* actors = renderer->GetActors(); // Get the collection of actors in the renderer
                actors->InitTraversal(); // Initialize the actors traversal

                vtkActor* actor_all = nullptr;
                while ((actor_all = actors->GetNextActor()) != nullptr) {
                    updatethickness_2(actor_all, thickness);
                }
            }
            else if (thickness_mode == "Specific shape") {
                QMessageBox messageBox_edit;
                QComboBox* comboBox = new QComboBox(); // Create a new QComboBox object
                for (const auto& shapeName : drawnShapes) {
                    std::cout << shapeName.toStdString() << " ";
                    comboBox->addItem(shapeName);
                }
                messageBox_edit.layout()->addWidget(comboBox); // Add the QComboBox to the QMessageBox's layout
                messageBox_edit.exec(); // Show the QMessageBox
                QString selectedShape = comboBox->currentText(); // Get the currently selected shape from the QComboBox
                if (selectedShape == "Circle") {
                    updatethickness_2(actor_circle, thickness);
                }
                else if (selectedShape == "Line") {
                    updatethickness_2(actor, thickness);
                }
                else if (selectedShape == "Ellipse") {
                    updatethickness_2(actor_Ellipse, thickness);
                }
                else if (selectedShape == "Arc") {
                    updatethickness_2(actor_Arc, thickness);
                }
                else if (selectedShape == "Sphere") {
                    updatethickness_2(actor_Football, thickness);
                }
                else if (selectedShape == "Hexahedron") {
                    updatethickness_2(actor_Hexahedron, thickness);
                }
                else if (selectedShape == "Regular Polygon") {
                    updatethickness_2(actor_Regular_Polygon, thickness);
                }
                else if (selectedShape == "Cylinder") {
                    updatethickness_2(actor_Cylinder, thickness);
                }
                else if (selectedShape == "Square") {
                    updatethickness_2(actor_Square, thickness);
                }
                else if (selectedShape == "Star") {
                    updatethickness_2(actor_Star, thickness);
                }
                else if (selectedShape == "Polyline") {
                    updatethickness_2(PolyLine_actor, thickness);
                }
                else if (selectedShape == "Polygon") {
                    updatethickness_2(Polygon_actor, thickness);
                }
                else if (selectedShape == "Ellipsoid") {
                    updatethickness_2(Ellipsoid_actor, thickness);
                }
                else {
                    return;
                }
            }
        }
        else {
            vtkNew<MouseInteractorStyleDrawLine> style;
            //style->setShapeName(shape_name);
            style->setDrawFlag(false);
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            if (shape_name == "Circle") {
                updatethickness_2(actor_circle, thickness);
            }
            else if (shape_name == "Line") {
                updatethickness_2(actor, thickness);
            }
            else if (shape_name == "Ellipse") {
                updatethickness_2(actor_Ellipse, thickness);
            }
            else if (shape_name == "Arc") {
                updatethickness_2(actor_Arc, thickness);
            }
            else if (shape_name == "Sphere") {
                updatethickness_2(actor_Football, thickness);
            }
            else if (shape_name == "Hexahedron") {
                updatethickness_2(actor_Hexahedron, thickness);
            }
            else if (shape_name == "Regular Polygon") {
                updatethickness_2(actor_Regular_Polygon, thickness);
            }
            else if (shape_name == "Cylinder") {
                updatethickness_2(actor_Cylinder, thickness);
            }
            else if (shape_name == "Square") {
                updatethickness_2(actor_Square, thickness);
            }
            else if (shape_name == "Star") {
                updatethickness_2(actor_Star, thickness);
            }
            else if (shape_name == "Polyline") {
                updatethickness_2(PolyLine_actor, thickness);
            }
            else if (shape_name == "Polygon") {
                updatethickness_2(Polygon_actor, thickness);
            }
            else if (shape_name == "Ellipsoid") {
                updatethickness_2(Ellipsoid_actor, thickness);
            }
            else {
                return;
            }
        }
        window->Render();
    }

    void add_shape_list(string shape_name, QListWidget& shapeListWidget) {
        QString qshape_name = QString::fromStdString(shape_name);
        QListWidgetItem* item = new QListWidgetItem(qshape_name, &shapeListWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    }

    void Change_Shapes(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window, QListWidget& shapeListWidget)
    {
        std::string shape_name = comboBox->currentText().toStdString();
        drawn_shapes.push(shape_name); // Add the shape name to the stack
        vtkNew<MouseInteractorStyleDrawLine> style;
        style->setShapeName(shape_name);
        style->setDrawFlag(true);
        if (shape_name == "Circle") {
            QMessageBox messageBox;
            messageBox.setText("Choose Drawning Style");
            QAbstractButton* button = messageBox.addButton(QMessageBox::tr("Mouse Click"), QMessageBox::YesRole);
            QAbstractButton* button_1 = messageBox.addButton(QMessageBox::tr("Enter points"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            mode_circle = buttonText.toStdString();
            if (mode_circle == "Enter points") {
                bool ok;
                Radius_Circle = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the circle:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
            }
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            circle_deleted = false;
        }
        else if (shape_name == "Sphere") {
            QMessageBox messageBox;
            messageBox.setText("Choose Drawning Style");
            QAbstractButton* button = messageBox.addButton(QMessageBox::tr("Mouse Click"), QMessageBox::YesRole);
            QAbstractButton* button_1 = messageBox.addButton(QMessageBox::tr("Enter points"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            mode_Sphere = buttonText.toStdString();
            if (mode_Sphere == "Enter points") {
                bool ok;
                Radius_Sphere = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Sphere:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
            }
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            sphere_3D = true;
            Sphere_deleted = false;
        }
        else if (shape_name == "Arc") {
            QMessageBox messageBox;
            messageBox.setText("Choose Drawning Style");
            QAbstractButton* button = messageBox.addButton(QMessageBox::tr("Mouse Click"), QMessageBox::YesRole);
            QAbstractButton* button_1 = messageBox.addButton(QMessageBox::tr("Enter points"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            mode_arc = buttonText.toStdString();
            if (mode_arc == "Enter points") {
                bool ok;
                Radius_Arc = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Arc:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
            }
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            Arc_deleted = false;
        }
        else if (shape_name == "Hexahedron")
        {
            bool ok;
            Radius_Hexahedron = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Hexahedron:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            cube_3D = true;
            Hexahedron_deleted = false;
        }
        else if (shape_name == "Line")
        {
            // Ask user for filled or non-filled region
            QMessageBox messageBox;
            messageBox.setText("Choose Drawning Style");
            QAbstractButton* button = messageBox.addButton(QMessageBox::tr("Mouse Click"), QMessageBox::YesRole);
            QAbstractButton* button_1 = messageBox.addButton(QMessageBox::tr("Enter points"), QMessageBox::YesRole);
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
                line_mouse_enter = false;
            }
            else {
                vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
                renderWindowInteractor->SetRenderWindow(window);
                // Set the custom interactor style
                style->SetRenderer(renderer);


                style->setPolygonFlag(false);
                renderWindowInteractor->SetInteractorStyle(style.Get());
            }
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            line_deleted = false;
        }
        else if (shape_name == "Polyline")
        {
            bool ok;
            NO_POINTS_polyline = QInputDialog::getDouble(nullptr, "Enter Points", "Enter the PolyLine Points:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style
            style->SetRenderer(renderer);


            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            polyline_deleted = false;
        }
        else if (shape_name == "Polygon") {
            bool ok;
            NO_POINTS_polygon = QInputDialog::getDouble(nullptr, "Enter Points", "Enter the Polygon Points:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style
            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            Polygon_deleted = false;
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
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            Regular_Polygon_deleted = false;
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
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            cylinder_3D = true;
            Cylinder_deleted = false;
        }
        else if (shape_name == "Ellipse") {
            QMessageBox messageBox;
            messageBox.setText("Choose Drawning Style");
            QAbstractButton* button = messageBox.addButton(QMessageBox::tr("Mouse Click"), QMessageBox::YesRole);
            QAbstractButton* button_1 = messageBox.addButton(QMessageBox::tr("Enter points"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            mode_Ellipse = buttonText.toStdString();
            if (mode_Ellipse == "Enter points") {
                bool ok;
                MAJOR_AXIS = QInputDialog::getDouble(nullptr, "Enter Major Axis", "Enter the major axis (x) of the Ellipse:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                MINOR_AXIS = QInputDialog::getDouble(nullptr, "Enter Minor Axis", "Enter the minor axis (y) of the Ellipse:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
            }
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            ellipse_deleted = false;
        }
        else if (shape_name == "Square") {
            bool ok;
            Radius_Square = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Square:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            Square_deleted = false;
        }
        else if (shape_name == "Star") {
            bool ok;
            Radius_Star = QInputDialog::getDouble(nullptr, "Enter Radius", "Enter the radius of the Star:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            Star_deleted = false;
        }
        else if (shape_name == "Ellipsoid") {
            bool ok;
            semi_axis_x = QInputDialog::getDouble(nullptr, "Enter Semi-Axis-X", "Enter the semi-axis length along the x-axis:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            semi_axis_y = QInputDialog::getDouble(nullptr, "Enter Semi-Axis-Y", "Enter the semi-axis length along the y-axis:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            semi_axis_z = QInputDialog::getDouble(nullptr, "Enter Semi-Axis-Z", "Enter the semi-axis length along the z-axis:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);
            // Set the custom interactor style

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            drawnshapes_and_all_count(shape_name);
            add_shape_list(shape_name, shapeListWidget);
            Ellipsoid_3D = true;
            Ellipsoid_deleted = false;
        }
        window->Render();
    }

    void delete_shape(vtkSmartPointer<vtkLineSource> temp_Source, vtkSmartPointer<vtkActor> temp_actor) {
        // Set the color of the shape to match the background color
        temp_actor->GetProperty()->SetColor(renderer->GetBackground());
        // Remove points from the line source
        vtkSmartPointer<vtkPoints> emptyPoints = vtkSmartPointer<vtkPoints>::New();
        temp_Source->SetPoints(emptyPoints);
        count_shapes--;

        // Add the deleted shape to the stack
        deleted_sources.push(temp_Source);
        deleted_actors.push(temp_actor);
    }

    void erase_specific_shape(QString shape_name) {
        if (shape_name == "Circle") {
            double* color = actor_circle->GetProperty()->GetColor();
            Color_Circle = specify_color(color);
            delete_shape(circle_Source, actor_circle);
            drawnShapes.erase("Circle");
            circle_deleted = true;
        }
        else if (shape_name == "Line") {
            double* color = actor->GetProperty()->GetColor();
            Color_Line = specify_color(color);
            delete_shape(lineSource, actor);
            drawnShapes.erase("Line");
            line_deleted = true;
        }
        else if (shape_name == "Ellipse") {
            double* color = actor_Ellipse->GetProperty()->GetColor();
            Color_Ellipse = specify_color(color);
            delete_shape(Ellipse_Source, actor_Ellipse);
            drawnShapes.erase("Ellipse");
            ellipse_deleted = true;
        }
        else if (shape_name == "Arc") {
            double* color = actor_Arc->GetProperty()->GetColor();
            Color_Arc = specify_color(color);
            delete_shape(Arc_Source, actor_Arc);
            drawnShapes.erase("Arc");
            Arc_deleted = true;
        }
        else if (shape_name == "Sphere") {
            double* color = actor_Football->GetProperty()->GetColor();
            Color_Sphere = specify_color(color);
            delete_shape(Football_Source, actor_Football);
            drawnShapes.erase("Sphere");
            Sphere_deleted = true;
            sphere_3D = false;
        }
        else if (shape_name == "Hexahedron") {
            double* color = actor_Hexahedron->GetProperty()->GetColor();
            Color_Hexahedron = specify_color(color);
            delete_shape(Hexahedron_Source, actor_Hexahedron);
            drawnShapes.erase("Hexahedron");
            Hexahedron_deleted = true;
            cube_3D = false;
        }
        else if (shape_name == "Regular Polygon") {
            double* color = actor_Regular_Polygon->GetProperty()->GetColor();
            Color_Regular_Polygon = specify_color(color);
            delete_shape(Regular_Polygon_Source, actor_Regular_Polygon);
            drawnShapes.erase("Regular Polygon");
            Regular_Polygon_deleted = true;
        }
        else if (shape_name == "Cylinder") {
            double* color = actor_Cylinder->GetProperty()->GetColor();
            Color_Cylinder = specify_color(color);
            delete_shape(Cylinder_Source, actor_Cylinder);
            drawnShapes.erase("Cylinder");
            Cylinder_deleted = true;
            cylinder_3D = false;
        }
        else if (shape_name == "Square") {
            double* color = actor_Square->GetProperty()->GetColor();
            Color_Square = specify_color(color);
            delete_shape(Square_Source, actor_Square);
            drawnShapes.erase("Square");
            Square_deleted = true;
        }
        else if (shape_name == "Star") {
            double* color = actor_Star->GetProperty()->GetColor();
            Color_Star = specify_color(color);
            delete_shape(Star_Source, actor_Star);
            drawnShapes.erase("Star");
            Star_deleted = true;
        }
        else if (shape_name == "Polyline") {
            double* color = PolyLine_actor->GetProperty()->GetColor();
            Color_PolyLine = specify_color(color);
            delete_shape(PolyLine_Source, PolyLine_actor);
            drawnShapes.erase("Polyline");
            polyline_deleted = true;
        }
        else if (shape_name == "Polygon") {
            double* color = Polygon_actor->GetProperty()->GetColor();
            Color_Polygon = specify_color(color);
            delete_shape(Polygon_Source, Polygon_actor);
            drawnShapes.erase("Polygon");
            Polygon_deleted = true;
        }
        else if (shape_name == "Ellipsoid") {
            double* color = Ellipsoid_actor->GetProperty()->GetColor();
            Color_Ellipsoid = specify_color(color);
            delete_shape(Ellipsoid_Source, Ellipsoid_actor);
            drawnShapes.erase("Ellipsoid");
            Ellipsoid_deleted = true;
            Ellipsoid_3D = false;
        }
        else {
            return;
        }
    }

    void delete_all_shapes() {
        vtkActorCollection* actors = renderer->GetActors(); // Get the collection of actors in the renderer
        actors->InitTraversal(); // Initialize the actors traversal

        vtkActor* actor = nullptr;
        while ((actor = actors->GetNextActor()) != nullptr) {
            renderer->RemoveActor(actor); // Remove the actor from the renderer
        }
        while (!drawnShapes.empty()) {
            drawnShapes.erase(drawnShapes.begin()); // Erase the shape name from the set
        }
        cube_3D = false;
        cylinder_3D = false;
        Ellipsoid_3D = false;
        sphere_3D = false;
        circle_deleted = 1;
        ellipse_deleted = 1;
        Regular_Polygon_deleted = 1;
        Arc_deleted = 1;
        Cylinder_deleted = 1;
        Sphere_deleted = 1;
        Square_deleted = 1;
        Hexahedron_deleted = 1;
        Star_deleted = 1;
        line_deleted = 1;
        polyline_deleted = 1;
        Polygon_deleted = 1;
        Ellipsoid_deleted = 1;
    }

    void Delete(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window) {
        QString shape_name = comboBox->currentText();
        vtkNew<MouseInteractorStyleDrawLine> style;
        //style->setShapeName(shape_name);
        style->setDrawFlag(false);
        vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
        renderWindowInteractor->SetRenderWindow(window);

        style->SetRenderer(renderer);

        renderWindowInteractor->SetInteractorStyle(style.Get());
        if (count_shapes == 1) {
            delete_all_shapes();
            count_shapes = 0;
        }
        else {
            QMessageBox messageBox;
            messageBox.setText("Choose which one you want to delete");
            messageBox.addButton(QMessageBox::tr("Last shape drawn"), QMessageBox::YesRole);
            messageBox.addButton(QMessageBox::tr("All the Shapes"), QMessageBox::YesRole);
            messageBox.addButton(QMessageBox::tr("Specific shape"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            delete_mode = buttonText.toStdString();
            if (delete_mode == "Last shape drawn") {
                erase_specific_shape(shape_name);
            }
            else if (delete_mode == "All the Shapes") {
                delete_all_shapes();
                all_deleted = true;
                count_shapes = 0;
            }
            else if (delete_mode == "Specific shape") {
                QMessageBox messageBox_edit;
                QComboBox* comboBox = new QComboBox(); // Create a new QComboBox object
                for (const auto& shapeName : drawnShapes) {
                    std::cout << shapeName.toStdString() << " ";
                    comboBox->addItem(shapeName);
                }
                messageBox_edit.layout()->addWidget(comboBox); // Add the QComboBox to the QMessageBox's layout
                messageBox_edit.exec(); // Show the QMessageBox
                QString selectedShape = comboBox->currentText(); // Get the currently selected shape from the QComboBox
                erase_specific_shape(selectedShape);
            }
        }
        window->Render(); // Render the window to reflect the changes
    }

    void Translation(vtkSmartPointer<vtkLineSource> temp_source, vtkDataSetMapper* temp_mapper, double m14, double m24, double m34) {
        // Get the points of the circle shape
        vtkPoints* points = temp_source->GetPoints();

        // Create a new vtkPoints object to store the translated points
        vtkSmartPointer<vtkPoints> translatedPoints = vtkSmartPointer<vtkPoints>::New();

        // Loop through each point and apply translation
        for (vtkIdType i = 0; i < points->GetNumberOfPoints(); i++) {
            double originalPoint[3];
            points->GetPoint(i, originalPoint);
            double translatedPoint[4] = { originalPoint[0] + m14, originalPoint[1] + m24, originalPoint[2] + m34 , 1.0 };
            translatedPoints->InsertNextPoint(translatedPoint);
        }

        // Set the translated points to the circle shape's vtkPoints object
        temp_source->SetPoints(translatedPoints);

        // Update the mapper with the modified points
        temp_mapper->Update();
    }

    void Scaling(vtkSmartPointer<vtkLineSource> temp_source, double scalingFactorX, double scalingFactorY, double scalingFactorZ) {
        // Get the points of the circle
        vtkSmartPointer<vtkPoints> points = temp_source->GetPoints();
        for (int i = 0; i < points->GetNumberOfPoints(); i++) {
            double point[3];
            points->GetPoint(i, point);
            // Scale the x and y coordinates of the point
            point[0] = scalingFactorX * point[0];
            point[1] = scalingFactorY * point[1];
            point[2] = scalingFactorZ * point[2];
            points->SetPoint(i, point);
        }
        temp_source->Modified(); // Mark the source as modified
    }

    void Rotation_3D(vtkSmartPointer<vtkLineSource> temp_source, vtkDataSetMapper* temp_mapper, double angle, string rotation_axis) {
        // Convert the angle to radians
        angle *= vtkMath::Pi() / 180.0;

        // Get the points of the vtkLineSource object
        vtkPoints* points = temp_source->GetPoints();

        // Create a new vtkPoints object to store the translated points
        vtkSmartPointer<vtkPoints> translatedPoints = vtkSmartPointer<vtkPoints>::New();

        // Loop through each point and apply the rotation
        for (vtkIdType i = 0; i < points->GetNumberOfPoints(); i++) {
            double originalPoint[3];
            points->GetPoint(i, originalPoint);

            double Px = originalPoint[0];
            double Py = originalPoint[1];
            double Pz = originalPoint[2];

            double translatedPoint[3];

            // Apply the rotation based on the specified axis
            if (rotation_axis == "x-axis") {
                translatedPoint[0] = Px;
                translatedPoint[1] = Py * cos(angle) - Pz * sin(angle);
                translatedPoint[2] = Py * sin(angle) + Pz * cos(angle);
            }
            else if (rotation_axis == "y-axis") {
                translatedPoint[0] = Pz * sin(angle) + Px * cos(angle);
                translatedPoint[1] = Py;
                translatedPoint[2] = Pz * cos(angle) - Px * sin(angle);
            }
            else if (rotation_axis == "z-axis") {
                translatedPoint[0] = Px * cos(angle) - Py * sin(angle);
                translatedPoint[1] = Px * sin(angle) + Py * cos(angle);
                translatedPoint[2] = Pz;
            }

            // Insert the translated point into the new vtkPoints object
            translatedPoints->InsertNextPoint(translatedPoint);
        }

        // Set the translated points to the vtkLineSource object
        temp_source->SetPoints(translatedPoints);

        // Update the mapper with the modified points
        temp_mapper->Update();
    }

    void Rotation_2D(vtkSmartPointer<vtkLineSource> temp_source, vtkDataSetMapper* temp_mapper, double angle) {
        angle *= vtkMath::Pi() / 180.0; // Convert the angle to radians
        vtkPoints* points = temp_source->GetPoints();

        // Create a new vtkPoints object to store the translated points
        vtkSmartPointer<vtkPoints> translatedPoints = vtkSmartPointer<vtkPoints>::New();

        // Loop through each point and apply translation
        for (vtkIdType i = 0; i < points->GetNumberOfPoints(); i++) {
            double originalPoint[3];
            points->GetPoint(i, originalPoint);
            double Px = originalPoint[0];
            double Py = originalPoint[1];
            double translatedPoint[3] = { Px * cos(angle) - Py * sin(angle),  Px * sin(angle) + Py * cos(angle), 1.0 };
            translatedPoints->InsertNextPoint(translatedPoint);
        }

        // Set the translated points to the circle shape's vtkPoints object
        temp_source->SetPoints(translatedPoints);

        // Update the mapper with the modified points
        temp_mapper->Update();
    }

    void Shearing_2D(vtkLineSource* temp_source, double h, string Shearing_2D_direc) {
        // Get the current coordinates of the points in the source
        vtkSmartPointer<vtkPoints> points = temp_source->GetPoints();

        if (Shearing_2D_direc == "x-axis") {
            // Apply the Shearing_2D transformation to each point
            for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
                double point[3];
                points->GetPoint(i, point);
                double Px = point[0];
                double Py = point[1];

                // Apply the Shearing_2D equation
                double Qx = Px + h * Py;
                double Qy = Py;

                // Set the new coordinates for the transformed point
                points->SetPoint(i, Qx, Qy, point[2]);
            }
        }
        else if (Shearing_2D_direc == "y-axis") {
            // Apply the Shearing_2D transformation to each point
            for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
                double point[3];
                points->GetPoint(i, point);
                double Px = point[0];
                double Py = point[1];

                // Apply the Shearing_2D equation
                double Qx = Px;
                double Qy = Py + h * Px;

                // Set the new coordinates for the transformed point
                points->SetPoint(i, Qx, Qy, point[2]);
            }
        }
        else {
            return;
        }
        // Update the source to reflect the transformed points
        temp_source->SetPoints(points);
        temp_source->Modified(); // Mark the source as modified
    }

    void Shearing_3D(vtkLineSource* temp_source, double h, string Shearing_3D_direc) {
        // Get the current coordinates of the points in the source
        vtkSmartPointer<vtkPoints> points = temp_source->GetPoints();

        if (Shearing_3D_direc == "x-axis") {
            // Apply the Shearing_2D transformation to each point
            for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
                double point[3];
                points->GetPoint(i, point);
                double Px = point[0];
                double Py = point[1];
                double Pz = point[2];

                // Apply the Shearing_2D equation
                double Qx = Px;
                double Qy = Py + h * Px;
                double Qz = Pz + h * Px;

                // Set the new coordinates for the transformed point
                points->SetPoint(i, Qx, Qy, Qz);
            }
        }
        else if (Shearing_3D_direc == "y-axis") {
            // Apply the Shearing_2D transformation to each point
            for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
                double point[3];
                points->GetPoint(i, point);
                double Px = point[0];
                double Py = point[1];
                double Pz = point[2];


                // Apply the Shearing_2D equation
                double Qx = Px + h * Py;
                double Qy = Py;
                double Qz = Pz + h * Py;

                // Set the new coordinates for the transformed point
                points->SetPoint(i, Qx, Qy, Qz);
            }
        }
        else if (Shearing_3D_direc == "z-axis") {
            // Apply the Shearing_2D transformation to each point
            for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
                double point[3];
                points->GetPoint(i, point);
                double Px = point[0];
                double Py = point[1];
                double Pz = point[2];


                // Apply the Shearing_2D equation
                double Qx = Px + h * Pz;
                double Qy = Py + h * Pz;
                double Qz = Pz;

                // Set the new coordinates for the transformed point
                points->SetPoint(i, Qx, Qy, Qz);
            }
        }
        else {
            return;
        }
        // Update the source to reflect the transformed points
        temp_source->SetPoints(points);
        temp_source->Modified(); // Mark the source as modified
    }

    void transform_modes(QString transform_state, QString shape_name) {
        if (transform_state == "Translation") {
            bool ok;
            double x = QInputDialog::getDouble(nullptr, "Enter Translation X", "Enter the Translation X:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            double y = QInputDialog::getDouble(nullptr, "Enter Translation Y", "Enter the Translation Y:", 0.0, -100.0, 100.0, 2, &ok);
            if (!ok) {
                return;
            }
            if (shape_name == "Circle") {
                Translation(circle_Source, mapper_circle, x, y, 0);
            }
            else if (shape_name == "Line") {
                Translation(lineSource, mapper, x, y, 0);
            }
            else if (shape_name == "Ellipse") {
                Translation(Ellipse_Source, mapper_Ellipse, x, y, 0);
            }
            else if (shape_name == "Arc") {
                Translation(Arc_Source, mapper_Arc, x, y, 0);
            }
            else if (shape_name == "Sphere") {
                double z = QInputDialog::getDouble(nullptr, "Enter Translation Z", "Enter the Translation Z:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                Translation(Football_Source, mapper_Football, x, y, z);
            }
            else if (shape_name == "Hexahedron") {
                double z = QInputDialog::getDouble(nullptr, "Enter Translation Z", "Enter the Translation Z:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                Translation(Hexahedron_Source, mapper_Hexahedron, x, y, z);
            }
            else if (shape_name == "Regular Polygon") {
                Translation(Regular_Polygon_Source, mapper_Regular_Polygon, x, y, 0);
            }
            else if (shape_name == "Cylinder") {
                double z = QInputDialog::getDouble(nullptr, "Enter Translation Z", "Enter the Translation Z:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                Translation(Cylinder_Source, mapper_Cylinder, x, y, z);
            }
            else if (shape_name == "Square") {
                Translation(Square_Source, mapper_Square, x, y, 0);
            }
            else if (shape_name == "Star") {
                Translation(Star_Source, mapper_Star, x, y, 0);
            }
            else if (shape_name == "Polyline") {
                Translation(PolyLine_Source, PolyLine_mapper, x, y, 0);
            }
            else if (shape_name == "Polygon") {
                Translation(Polygon_Source, Polygon_mapper, x, y, 0);
            }
            else if (shape_name == "Ellipsoid") {
                double z = QInputDialog::getDouble(nullptr, "Enter Translation Z", "Enter the Translation Z:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                Translation(Ellipsoid_Source, Ellipsoid_mapper, x, y, z);
            }
            else {
                return;
            }
        }
        else if (transform_state == "Scaling") {
            bool ok;
            double scalingFactorX = QInputDialog::getDouble(nullptr, "Enter Scaling factor X", "Enter the Scaling factor in X direction:", 0.0, -100.0, 100.0, 2, &ok);
            // Example scaling factor in x-direction
            if (!ok) {
                return;
            }
            double scalingFactorY = QInputDialog::getDouble(nullptr, "Enter Scaling factor Y", "Enter the Scaling factor in Y direction:", 0.0, -100.0, 100.0, 2, &ok);
            // Example scaling factor in y-direction
            if (!ok) {
                return;
            }
            if (shape_name == "Circle") {
                Scaling(circle_Source, scalingFactorX, scalingFactorY, 0);
            }
            else if (shape_name == "Line") {
                Scaling(lineSource, scalingFactorX, scalingFactorY, 0);
            }
            else if (shape_name == "Ellipse") {
                Scaling(Ellipse_Source, scalingFactorX, scalingFactorY, 0);
            }
            else if (shape_name == "Arc") {
                Scaling(Arc_Source, scalingFactorX, scalingFactorY, 0);
            }
            else if (shape_name == "Sphere") {
                double scalingFactorZ = QInputDialog::getDouble(nullptr, "Enter Scaling factor Z", "Enter the Scaling factor in Z direction:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                Scaling(Football_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
            }
            else if (shape_name == "Hexahedron") {
                double scalingFactorZ = QInputDialog::getDouble(nullptr, "Enter Scaling factor Z", "Enter the Scaling factor in Z direction:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                Scaling(Hexahedron_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
            }
            else if (shape_name == "Regular Polygon") {
                Scaling(Regular_Polygon_Source, scalingFactorX, scalingFactorY, 0);
            }
            else if (shape_name == "Cylinder") {
                double scalingFactorZ = QInputDialog::getDouble(nullptr, "Enter Scaling factor Z", "Enter the Scaling factor in Z direction:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                Scaling(Cylinder_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
            }
            else if (shape_name == "Square") {
                Scaling(Square_Source, scalingFactorX, scalingFactorY, 0);
            }
            else if (shape_name == "Star") {
                Scaling(Star_Source, scalingFactorX, scalingFactorY, 0);
            }
            else if (shape_name == "Polyline") {
                Scaling(PolyLine_Source, scalingFactorX, scalingFactorY, 0);
            }
            else if (shape_name == "Polygon") {
                Scaling(Polygon_Source, scalingFactorX, scalingFactorY, 0);
            }
            else if (shape_name == "Ellipsoid") {
                double scalingFactorZ = QInputDialog::getDouble(nullptr, "Enter Scaling factor Z", "Enter the Scaling factor in Z direction:", 0.0, -100.0, 100.0, 2, &ok);
                if (!ok) {
                    return;
                }
                Scaling(Ellipsoid_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
            }
            else {
                return;
            }
        }
        else if (transform_state == "Rotating") {
            string rotation_direc = "x-axis";
            if (shape_name == "Sphere" || shape_name == "Hexahedron" || shape_name == "Cylinder" || shape_name == "Ellipsoid") {
                QMessageBox messageBox;
                messageBox.setText("Choose which axis you wand to rotate aroud");
                messageBox.addButton(QMessageBox::tr("x-axis"), QMessageBox::YesRole);
                messageBox.addButton(QMessageBox::tr("y-axis"), QMessageBox::YesRole);
                messageBox.addButton(QMessageBox::tr("z-axis"), QMessageBox::YesRole);
                messageBox.exec();
                QString rotation_direc_1 = messageBox.clickedButton()->text();
                rotation_direc = rotation_direc_1.toStdString();
            }
            bool ok;
            double angle = QInputDialog::getDouble(nullptr, "Enter the Angle", "Enter the Angle of Rotation_2D:", 0.0, -100.0, 360, 2, &ok);
            if (!ok) {
                return;
            }
            if (shape_name == "Circle") {
                Rotation_2D(circle_Source, mapper_circle, angle);
            }
            else if (shape_name == "Line") {
                Rotation_2D(lineSource, mapper, angle);
            }
            else if (shape_name == "Ellipse") {
                Rotation_2D(Ellipse_Source, mapper_Ellipse, angle);
            }
            else if (shape_name == "Arc") {
                Rotation_2D(Arc_Source, mapper_Arc, angle);
            }
            else if (shape_name == "Sphere") {
                Rotation_3D(Football_Source, mapper_Football, angle, rotation_direc);
            }
            else if (shape_name == "Hexahedron") {
                Rotation_3D(Hexahedron_Source, mapper_Hexahedron, angle, rotation_direc);
            }
            else if (shape_name == "Regular Polygon") {
                Rotation_2D(Regular_Polygon_Source, mapper_Regular_Polygon, angle);
            }
            else if (shape_name == "Cylinder") {
                Rotation_3D(Cylinder_Source, mapper_Cylinder, angle, rotation_direc);
            }
            else if (shape_name == "Square") {
                Rotation_2D(Square_Source, mapper_Square, angle);
            }
            else if (shape_name == "Star") {
                Rotation_2D(Star_Source, mapper_Star, angle);
            }
            else if (shape_name == "Polyline") {
                Rotation_2D(PolyLine_Source, PolyLine_mapper, angle);
            }
            else if (shape_name == "Polygon") {
                Rotation_2D(Polygon_Source, Polygon_mapper, angle);
            }
            else if (shape_name == "Ellipsoid") {
                Rotation_3D(Ellipsoid_Source, Ellipsoid_mapper, angle, rotation_direc);
            }
            else {
                return;
            }
        }
        else if (transform_state == "Shearing") {
            QMessageBox messageBox;
            messageBox.setText("Choose which direction you want to shear to");
            messageBox.addButton(QMessageBox::tr("x-axis"), QMessageBox::YesRole);
            messageBox.addButton(QMessageBox::tr("y-axis"), QMessageBox::YesRole);
            if (shape_name == "Sphere" || shape_name == "Hexahedron" || shape_name == "Cylinder" || shape_name == "Ellipsoid") {
                messageBox.addButton(QMessageBox::tr("z-axis"), QMessageBox::YesRole);
            }
            messageBox.exec();
            QString Shearing_direc = messageBox.clickedButton()->text();
            Shearing_direc_mode = Shearing_direc.toStdString();
            bool ok;
            double h = QInputDialog::getDouble(nullptr, "Enter the Shearing factor", "Enter the factor of Shearing:", 0.0, -100.0, 360, 2, &ok);
            if (!ok) {
                return;
            }  // Specify the desired Shearing_2D factor
            if (shape_name == "Circle") {
                Shearing_2D(circle_Source, h, Shearing_direc_mode);
            }
            else if (shape_name == "Line") {
                Shearing_2D(lineSource, h, Shearing_direc_mode);
            }
            else if (shape_name == "Ellipse") {
                Shearing_2D(Ellipse_Source, h, Shearing_direc_mode);
            }
            else if (shape_name == "Arc") {
                Shearing_2D(Arc_Source, h, Shearing_direc_mode);
            }
            else if (shape_name == "Sphere") {
                Shearing_3D(Football_Source, h, Shearing_direc_mode);
            }
            else if (shape_name == "Hexahedron") {
                Shearing_3D(Hexahedron_Source, h, Shearing_direc_mode);
            }
            else if (shape_name == "Regular Polygon") {
                Shearing_2D(Regular_Polygon_Source, h, Shearing_direc_mode);
            }
            else if (shape_name == "Cylinder") {
                Shearing_3D(Cylinder_Source, h, Shearing_direc_mode);
            }
            else if (shape_name == "Square") {
                Shearing_2D(Square_Source, h, Shearing_direc_mode);
            }
            else if (shape_name == "Star") {
                Shearing_2D(Star_Source, h, Shearing_direc_mode);
            }
            else if (shape_name == "Polyline") {
                Shearing_2D(PolyLine_Source, h, Shearing_direc_mode);
            }
            else if (shape_name == "Polygon") {
                Shearing_2D(Polygon_Source, h, Shearing_direc_mode);
            }
            else if (shape_name == "Ellipsoid") {
                Shearing_3D(Ellipsoid_Source, h, Shearing_direc_mode);
            }
            else {
                return;
            }
        }
    }

    void Translation_all_shapes(vtkSmartPointer<vtkActor> tempactor, double x, double y, double z) {
        if (tempactor == actor) {
            Translation(lineSource, mapper, x, y, 0);
        }
        else if (tempactor == actor_circle) {
            Translation(circle_Source, mapper_circle, x, y, 0);
        }
        else if (tempactor == actor_Arc) {
            Translation(Arc_Source, mapper_Arc, x, y, 0);
        }
        else if (tempactor == actor_Cylinder) {
            Translation(Cylinder_Source, mapper_Cylinder, x, y, 0);
        }
        else if (tempactor == actor_Ellipse) {
            Translation(Ellipse_Source, mapper_Ellipse, x, y, 0);
        }
        else if (tempactor == actor_Football) {
            Translation(Football_Source, mapper_Football, x, y, z);
        }
        else if (tempactor == actor_Hexahedron) {
            Translation(Hexahedron_Source, mapper_Hexahedron, x, y, 0);
        }
        else if (tempactor == actor_Regular_Polygon) {
            Translation(Regular_Polygon_Source, mapper_Regular_Polygon, x, y, 0);
        }
        else if (tempactor == actor_Square) {
            Translation(Square_Source, mapper_Square, x, y, 0);
        }
        else if (tempactor == actor_Star) {
            Translation(Star_Source, mapper_Star, x, y, 0);
        }
        else if (tempactor == Polygon_actor) {
            Translation(Polygon_Source, Polygon_mapper, x, y, 0);
        }
        else if (tempactor == PolyLine_actor) {
            Translation(PolyLine_Source, PolyLine_mapper, x, y, 0);
        }
        else if (tempactor == Ellipsoid_actor) {
            Translation(Ellipsoid_Source, Ellipsoid_mapper, x, y, 0);
        }
        else {
            return;
        }
    }

    void Scaling_all_shapes(vtkSmartPointer<vtkActor> tempactor, double scalingFactorX, double scalingFactorY, double scalingFactorZ) {
        if (tempactor == actor) {
            Scaling(lineSource, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == actor_circle) {
            Scaling(circle_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == actor_Arc) {
            Scaling(Arc_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == actor_Cylinder) {
            Scaling(Cylinder_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == actor_Ellipse) {
            Scaling(Ellipse_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == actor_Football) {
            Scaling(Football_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == actor_Hexahedron) {
            Scaling(Hexahedron_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == actor_Regular_Polygon) {
            Scaling(Regular_Polygon_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == actor_Square) {
            Scaling(Square_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == actor_Star) {
            Scaling(Star_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == Polygon_actor) {
            Scaling(Polygon_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == PolyLine_actor) {
            Scaling(PolyLine_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else if (tempactor == Ellipsoid_actor) {
            Scaling(Ellipsoid_Source, scalingFactorX, scalingFactorY, scalingFactorZ);
        }
        else {
            return;
        }
    }

    void Rotating_all_shapes(vtkSmartPointer<vtkActor> tempactor, double angle, string rotation_direc) {
        if (tempactor == actor) {
            Rotation_2D(lineSource, mapper, angle);
        }
        else if (tempactor == actor_circle) {
            Rotation_2D(circle_Source, mapper_circle, angle);
        }
        else if (tempactor == actor_Arc) {
            Rotation_2D(Arc_Source, mapper_Arc, angle);
        }
        else if (tempactor == actor_Cylinder) {
            Rotation_3D(Cylinder_Source, mapper_Cylinder, angle, rotation_direc);
        }
        else if (tempactor == actor_Ellipse) {
            Rotation_2D(Ellipse_Source, mapper_Ellipse, angle);
        }
        else if (tempactor == actor_Football) {
            Rotation_3D(Football_Source, mapper_Football, angle, rotation_direc);
        }
        else if (tempactor == actor_Hexahedron) {
            Rotation_3D(Hexahedron_Source, mapper_Hexahedron, angle, rotation_direc);
        }
        else if (tempactor == actor_Regular_Polygon) {
            Rotation_2D(Regular_Polygon_Source, mapper_Regular_Polygon, angle);
        }
        else if (tempactor == actor_Square) {
            Rotation_2D(Square_Source, mapper_Square, angle);
        }
        else if (tempactor == actor_Star) {
            Rotation_2D(Star_Source, mapper_Star, angle);
        }
        else if (tempactor == Polygon_actor) {
            Rotation_2D(Polygon_Source, Polygon_mapper, angle);
        }
        else if (tempactor == PolyLine_actor) {
            Rotation_2D(PolyLine_Source, PolyLine_mapper, angle);
        }
        else if (tempactor == Ellipsoid_actor) {
            Rotation_3D(Ellipsoid_Source, Ellipsoid_mapper, angle, rotation_direc);
        }
        else {
            return;
        }
    }

    void Shearing_all_shapes(vtkSmartPointer<vtkActor> tempactor, double h, string Shearing_direc) {
        if (tempactor == actor) {
            Shearing_2D(lineSource, h, Shearing_direc);
        }
        else if (tempactor == actor_circle) {
            Shearing_2D(circle_Source, h, Shearing_direc);
        }
        else if (tempactor == actor_Arc) {
            Shearing_2D(Arc_Source, h, Shearing_direc);
        }
        else if (tempactor == actor_Cylinder) {
            Shearing_3D(Cylinder_Source, h, Shearing_direc);
        }
        else if (tempactor == actor_Ellipse) {
            Shearing_2D(Ellipse_Source, h, Shearing_direc);
        }
        else if (tempactor == actor_Football) {
            Shearing_3D(Football_Source, h, Shearing_direc);
        }
        else if (tempactor == actor_Hexahedron) {
            Shearing_3D(Hexahedron_Source, h, Shearing_direc);
        }
        else if (tempactor == actor_Regular_Polygon) {
            Shearing_2D(Regular_Polygon_Source, h, Shearing_direc);
        }
        else if (tempactor == actor_Square) {
            Shearing_2D(Square_Source, h, Shearing_direc);
        }
        else if (tempactor == actor_Star) {
            Shearing_2D(Star_Source, h, Shearing_direc);
        }
        else if (tempactor == Polygon_actor) {
            Shearing_2D(Polygon_Source, h, Shearing_direc);
        }
        else if (tempactor == PolyLine_actor) {
            Shearing_2D(PolyLine_Source, h, Shearing_direc);
        }
        else if (tempactor == Ellipsoid_actor) {
            Shearing_3D(Ellipsoid_Source, h, Shearing_direc);
        }
        else {
            return;
        }
    }

    void Transform(QComboBox* comboBox_Transform, vtkGenericOpenGLRenderWindow* window, QComboBox* comboBox_Shapes) {
        QString transform_state = comboBox_Transform->currentText();
        QString shape_name = comboBox_Shapes->currentText();
        if (count_shapes > 1) {
            QMessageBox messageBox;
            messageBox.setText("Choose which shape you want to apply transformation");
            messageBox.addButton(QMessageBox::tr("Last shape drawn"), QMessageBox::YesRole);
            messageBox.addButton(QMessageBox::tr("All the Shapes"), QMessageBox::YesRole);
            messageBox.addButton(QMessageBox::tr("Specific shape"), QMessageBox::YesRole);
            messageBox.exec();
            QString buttonText = messageBox.clickedButton()->text();
            transform_mode = buttonText.toStdString();
            ///////////
            vtkNew<MouseInteractorStyleDrawLine> style;
            //style->setShapeName(shape_name);
            style->setDrawFlag(false);
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            // Set the custom interactor style
            if (transform_mode == "Last shape drawn") {
                transform_modes(transform_state, shape_name);
            }
            else if (transform_mode == "All the Shapes") {
                if (transform_state == "Translation") {
                    bool ok;
                    double x = QInputDialog::getDouble(nullptr, "Enter Transformation X", "Enter the Transformation X:", 0.0, -100.0, 100.0, 2, &ok);
                    if (!ok) {
                        return;
                    }
                    double y = QInputDialog::getDouble(nullptr, "Enter Transformation Y", "Enter the Transformation Y:", 0.0, -100.0, 100.0, 2, &ok);
                    if (!ok) {
                        return;
                    }
                    double z = 0;
                    if (sphere_3D == true || cube_3D == true || cylinder_3D == true || Ellipsoid_3D == true) {
                        z = QInputDialog::getDouble(nullptr, "Enter Transformation Z", "Enter the Transformation Z:", 0.0, -100.0, 100.0, 2, &ok);
                        if (!ok) {
                            return;
                        }
                    }
                    vtkActorCollection* actors = renderer->GetActors(); // Get the collection of actors in the renderer
                    actors->InitTraversal(); // Initialize the actors traversal
                    vtkActor* actor_all = nullptr;
                    while ((actor_all = actors->GetNextActor()) != nullptr) {
                        Translation_all_shapes(actor_all, x, y, z);
                    }
                }
                else if (transform_state == "Scaling") {
                    bool ok;
                    double scalingFactorX = QInputDialog::getDouble(nullptr, "Enter Scaling factor X", "Enter the Scaling factor in X direction:", 0.0, -100.0, 100.0, 2, &ok);
                    // Example scaling factor in x-direction
                    if (!ok) {
                        return;
                    }
                    double scalingFactorY = QInputDialog::getDouble(nullptr, "Enter Scaling factor Y", "Enter the Scaling factor in Y direction:", 0.0, -100.0, 100.0, 2, &ok);
                    // Example scaling factor in y-direction
                    if (!ok) {
                        return;
                    }
                    double scalingFactorZ = 0;
                    if (sphere_3D == true || cube_3D == true || cylinder_3D == true || Ellipsoid_3D == true) {
                        scalingFactorZ = QInputDialog::getDouble(nullptr, "Enter Scaling factor Z", "Enter the Scaling factor in Z direction:", 0.0, -100.0, 100.0, 2, &ok);
                        // Example scaling factor in y-direction
                        if (!ok) {
                            return;
                        }
                    }
                    vtkActorCollection* actors = renderer->GetActors(); // Get the collection of actors in the renderer
                    actors->InitTraversal(); // Initialize the actors traversal
                    vtkActor* actor_all = nullptr;
                    while ((actor_all = actors->GetNextActor()) != nullptr) {
                        Scaling_all_shapes(actor_all, scalingFactorX, scalingFactorY, scalingFactorZ);
                    }
                }
                else if (transform_state == "Rotating") {
                    string rotation_direc = "x-axis";
                    if (sphere_3D == true || cube_3D == true || cylinder_3D == true || Ellipsoid_3D == true) {
                        QMessageBox messageBox;
                        messageBox.setText("Choose which axis you wand to rotate aroud");
                        messageBox.addButton(QMessageBox::tr("x-axis"), QMessageBox::YesRole);
                        messageBox.addButton(QMessageBox::tr("y-axis"), QMessageBox::YesRole);
                        messageBox.addButton(QMessageBox::tr("z-axis"), QMessageBox::YesRole);
                        messageBox.exec();
                        QString rotation_direc_1 = messageBox.clickedButton()->text();
                        rotation_direc = rotation_direc_1.toStdString();
                    }
                    bool ok;
                    double angle = QInputDialog::getDouble(nullptr, "Enter the Angle", "Enter the Angle of Rotation_2D:", 0.0, -100.0, 360, 2, &ok);
                    if (!ok) {
                        return;
                    }
                    vtkActorCollection* actors = renderer->GetActors(); // Get the collection of actors in the renderer
                    actors->InitTraversal(); // Initialize the actors traversal
                    vtkActor* actor_all = nullptr;
                    while ((actor_all = actors->GetNextActor()) != nullptr) {
                        Rotating_all_shapes(actor_all, angle, rotation_direc);
                    }
                }
                else if (transform_state == "Shearing") {
                    bool ok;
                    QMessageBox messageBox;
                    messageBox.setText("Choose which shape you want to color");
                    messageBox.addButton(QMessageBox::tr("x-axis"), QMessageBox::YesRole);
                    messageBox.addButton(QMessageBox::tr("y-axis"), QMessageBox::YesRole);
                    if (sphere_3D == true || cube_3D == true || cylinder_3D == true || Ellipsoid_3D == true) {
                        messageBox.addButton(QMessageBox::tr("z-axis"), QMessageBox::YesRole);
                    }
                    messageBox.exec();
                    QString Shearing_direc = messageBox.clickedButton()->text();
                    Shearing_direc_mode = Shearing_direc.toStdString();
                    double h = QInputDialog::getDouble(nullptr, "Enter the Shearing factor", "Enter the factor of Shearing_2D:", 0.0, -100.0, 360, 2, &ok);
                    if (!ok) {
                        return;
                    }  // Specify the desired Shearing_2D factor
                    vtkActorCollection* actors = renderer->GetActors(); // Get the collection of actors in the renderer
                    actors->InitTraversal(); // Initialize the actors traversal
                    vtkActor* actor_all = nullptr;
                    while ((actor_all = actors->GetNextActor()) != nullptr) {
                        Shearing_all_shapes(actor_all, h, Shearing_direc_mode);
                    }
                }
            }
            else if (transform_mode == "Specific shape") {
                QMessageBox messageBox_edit;
                QComboBox* comboBox = new QComboBox(); // Create a new QComboBox object
                for (const auto& shapeName : drawnShapes) {
                    std::cout << shapeName.toStdString() << " ";
                    comboBox->addItem(shapeName);
                }
                messageBox_edit.layout()->addWidget(comboBox); // Add the QComboBox to the QMessageBox's layout
                messageBox_edit.exec(); // Show the QMessageBox
                QString selectedShape = comboBox->currentText(); // Get the currently selected shape from the QComboBox
                transform_modes(transform_state, selectedShape);
            }
        }
        else {
            vtkNew<MouseInteractorStyleDrawLine> style;
            //style->setShapeName(shape_name);
            style->setDrawFlag(false);
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            renderWindowInteractor->SetRenderWindow(window);

            style->SetRenderer(renderer);

            renderWindowInteractor->SetInteractorStyle(style.Get());
            transform_modes(transform_state, shape_name);
        }
        window->Render();
    }

    void Undo(QComboBox* comboBox, vtkGenericOpenGLRenderWindow* window) {
        QString shape_name = QString::fromStdString(drawn_shapes.top());
        drawn_shapes.pop(); // Remove the top shape name from the stack
        erase_specific_shape(shape_name);
        window->Render(); // Render the window to reflect the changes
    }

    void Redo(vtkGenericOpenGLRenderWindow* window) {
        if (deleted_sources.empty() || deleted_actors.empty()) {
            return;
        }

        // Redo the most recently deleted shape
        vtkSmartPointer<vtkLineSource> source1 = deleted_sources.top();
        deleted_sources.pop();

        vtkSmartPointer<vtkActor> actor1 = deleted_actors.top();
        deleted_actors.pop();

        renderer->AddActor(actor1);
        renderer->AddViewProp(actor1);
        window->AddRenderer(renderer);

        // If there are more shapes to redo, repeat the process
        if (!deleted_sources.empty() && !deleted_actors.empty()) {
            vtkSmartPointer<vtkLineSource> source2 = deleted_sources.top();
            deleted_sources.pop();

            vtkSmartPointer<vtkActor> actor2 = deleted_actors.top();
            deleted_actors.pop();

            renderer->AddActor(actor2);
            renderer->AddViewProp(actor2);
            window->AddRenderer(renderer);
        }

        window->Render();
    }
} // namespace
