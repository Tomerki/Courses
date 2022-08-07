package geometry;
import java.util.ArrayList;
import java.awt.Color;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class Rectangle {
    /**
     * this class generate a rectangels that we can define blocks by it.
     */
    private Point upperLeft, upperRight, lowerLeft, lowerRight;
    private final double width;
    private final double height;
    private Color color;
    private final Line downY, upY, leftX, rightX;

    //Create a new rectangle with location and width/height.

    /**
     * constructor thar initialize the new object field.
     * @param upperLeft - the upper left point of the new rectangle opbject.
     * @param width - the length of the up line and down line of the object.
     * @param height - the length of the right and left line of the object.
     */
    public Rectangle(Point upperLeft, double width, double height) {
        this.width = width;
        this.height = height;
        this.upperLeft = upperLeft;
        //initialize all the vertices of the object usint the upper left point the width and height.
        this.upperRight = new Point(upperLeft.getX() + width, upperLeft.getY());
        this.lowerLeft = new Point(upperLeft.getX(), upperLeft.getY() + height);
        this.lowerRight = new Point(upperLeft.getX() + this.width,  upperLeft.getY() + this.height);
        this.color = null;
        //define the object line so its easier to find an intersection.
        this.downY = new Line(this.lowerLeft, this.lowerRight);
        this.upY = new Line(this.upperLeft, this.upperRight);
        this.leftX = new Line(this.upperLeft, this.lowerLeft);
        this.rightX = new Line(this.upperRight, this.lowerRight);
    }

    /**
     * another constructor that can get also a color.
       we usind the original constructor to initialize all the other field.
     * @param upperLeft -point for define the object
     * @param width - object width
     * @param height - object height.
     * @param color - object color.
     */
    public Rectangle(Point upperLeft, double width, double height, Color color) {
        this(upperLeft, width, height);
        this.color = color;
    }

    // Return a (possibly empty) List of intersection points
    // with the specified line.

    /**
     * the function checks if there is an intersection between a line and an object.
       if there is, we add it to a new array that save all the intersection point with this object.
     * @param line - the line to check is its intersecting with the object.
     * @return - return the list with the intersection point or an empty list if there are no intersections.
     */
    public java.util.List<Point> intersectionPoints(Line line) {
        ArrayList<Point> intersectionPointsArray = new ArrayList<>();
        if (line.isIntersecting(this.downY)) {
            intersectionPointsArray.add(line.intersectionWith(this.downY));
        }
        if (line.isIntersecting(this.upY)) {
            intersectionPointsArray.add(line.intersectionWith(this.upY));
        }
        if (line.isIntersecting(this.leftX)) {
            intersectionPointsArray.add(line.intersectionWith(this.leftX));
        }
        if (line.isIntersecting(this.rightX)) {
            intersectionPointsArray.add(line.intersectionWith(this.rightX));
        }
        return intersectionPointsArray;
    }

    // Return the width and height of the rectangle

    /**
     * get the object width.
     * @return object width
     */
    public double getWidth() {
        return this.width;
    }

    /**
     * get the object height.
     * @return object height.
     */
    public double getHeight() {
        return this.height;
    }

    /**
     * get an access to the field out side the class.
     * @return the upper left point of the rectangle.
     */
    public Point getUpperLeft() {
        return this.upperLeft;
    }

    /**
     * method that set the location of the rectangle.
     * @param point - the point we want to set the rectangle to it.
     */
    public void setUpperLeft(Point point) {
        this.upperLeft = point;
    }

    /**
     *get an access to the field out side the class.
     * @return the upper right point of the rectangle.
     */
    public Point getUpperRight() {
        return this.upperRight;
    }

    /**
     *get an access to the field out side the class.
     * @return the lower left point of the rectangle.
     */
    public Point getLowerLeft() {
        return this.lowerLeft;
    }
    /**
     *get an access to the field out side the class.
     * @return the color of the rectangle.
     */
    public Color getColor() {
        return this.color;
    }
    /**
     *get an access to the field out side the class.
     * @return the down line of the rectangle.
     */
    public Line getDownYLine() {
        return this.downY;
    }

    /**
     *get an access to the field out side the class.
     * @return the upper line of the rectangle.
     */
    public Line getUpYLine() {
        return this.upY;
    }

    /**
     *get an access to the field out side the class.
     * @return the left line of the rectangle.
     */
    public Line getLeftXLine() {
        return this.leftX;
    }

    /**
     *get an access to the field out side the class.
     * @return the right line of the rectangle.
     */
    public Line getRightXLine() {
        return this.rightX;
    }

    /**
     * function get a point and checks if the point between the rectangles point value.
       if yes - true, else - false.
     * @param point - point to check.
     * @return true/ false
     */
    public boolean ifPointInsideMe(Point point) {
        if ((int) point.getX() >= (int) this.getUpperLeft().getX()
                && (int) point.getX() <= (int) this.getUpperRight().getX()) {
            return (int) point.getY() >= (int) this.getUpperLeft().getY()
                    && (int) point.getY() <= (int) this.getLowerLeft().getY();
        }
        return false;
    }

    /**
     * method that set the rectangle color.
     * @param c - the new color.
     */
    public void setColor(Color c) {
        this.color = c;
    }
}




