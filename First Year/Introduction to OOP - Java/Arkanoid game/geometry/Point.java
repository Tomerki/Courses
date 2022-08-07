package geometry;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class Point {
    /**
     * Point class define a Point that contained 2 doubles
     * the first - describe the value of x on the coordinate system,
     * the second number describe the value of y on the coordinate system.
     */
    //fields - two double numbers that defined the value of the Point.
    private double x, y;

    /**Constructor.
     * make up a Point on the coordinate system with the required
     * @param x - the required x value for the object
     * @param y - the required y value for the object
     */
    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }
    /**method
     * the method calculate the distance between this object(Point) and the Other Point.
     * @param other - some Point
     * @return - the return value is the distance between this point to the required Point(other)
     */
    public double distance(Point other) {
        //using the distance formula to calculate the distance.
        return Math.sqrt(Math.pow(this.getX() - other.getX(), 2) + Math.pow(this.getY() - other.getY(), 2));
    }
    /**
     * checks if 2 Points are equal.
     * @param other - Point that we want to check if our object (Point) is equal to her.
     * @return - return true if the two Points identical.
     */
    public boolean equals(Point other) {
        double epsilon = Math.pow(10, -8);
        //checks if Points equal by epsilon.
        if ((Math.abs(this.getX() - other.getX()) < epsilon) && (Math.abs(this.getY() - other.getY()) < epsilon)) {
            //return True if equal, else false.
            return true;
        }
        return false;
    }
    /**
     * check the value of x.
     * @return x Point value
     */
    public double getX() {
        return this.x;
    }
    /**
     * check the value of y.
     * @return y Point value
     */
    public double getY() {
        return this.y;
    }
}
