package geometry;
import java.util.List;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class Line {
    /**
     * Line class define a line that Defined by two points ( from Point Class ).
     */
    //fields - two Point - one the start of the line and the other the end of it.
    private final Point start, end;
    /**Constructor.
     * the Constructor initialize the object(Line) with the required Points.
     * @param start - the start Point of the Line
     * @param end - the end Point of the line.
     */
    public Line(Point start, Point end) {
        // with if-else statement we checks which Point is the start and which Point is the end.
        if ((start.getX() == end.getX()) && (start.getY() >= end.getY())) {
            this.start = end;
            this.end = start;
        } else if ((start.getX() == end.getX()) && (start.getY() <= end.getY())) {
            this.start = start;
            this.end = end;
        } else if (start.getX() > end.getX()) {
            this.end = start;
            this.start = end;
        } else {
            this.start = start;
            this.end = end;
        }
    }
    /**Constructor.
     * another constructor that deals with the case that the parameters for the
     input are 4 numbers instead two Points.
     * @param x1 - first Point x value
     * @param y1 - first Point y value
     * @param x2 - second Point x value
     * @param y2 - second Point x value
     */
    public Line(double x1, double y1, double x2, double y2) {
        //using the original constructor.
        this(new Point(x1, y1), new Point(x2, y2));
    }
    /**
     * check the length between the start point of the line to the end point of the line.
     while we define a line the constructor checks which Point is the start point of the line
     and which is the end point, that help us checks the length because we already know
     for sure that each Point got the correct value.
     * @return - return the length of the object(this line)
     */
    public double length() {
        double epsilon = Math.pow(10, -3);
        //if same x value - return y1-y2
        if (Math.abs((this.start.getX() - this.end.getX())) < epsilon) {
            return ((this.start.getY()) - (this.end.getY()));
        }
        //if same y value - return x1-x2
        if (Math.abs((this.start.getY() - this.end.getY())) < epsilon) {
            return ((this.start.getX() - this.end.getX()));
        }
        //else return the length using distance method
        return this.start.distance(end);
    }
    /**
     * calculate the middle point of the line.
     * @return the middle Point.
     */
    public Point middle() {
        return new Point((this.start.getX() + this.end.getX()) / 2, (this.start.getY() + this.end.getY()) / 2);
    }
    /**
     * get the start point of the line.
     * @return - return the start Point of the line
     */
    public Point start() {
        //this mean that we point for the specific object
        return this.start;
    }
    /**
     * get the end point of the line.
     * @return - return the end Point of the line
     */
    public Point end() {
        return this.end;
    }
    /**
     * checks if two lines are intersecting by using the function
     intersectionWith, if intersectionWith return a Point so isIntersecting return True,
     else false.
     * @param other - line that we want to check if our line intersecting with it.
     * @return - return true if the two lines are intersecting, else false
     */
    public boolean isIntersecting(Line other) {
        //checks if the 2 lines have the same scope.
        if ((doublesEquals(this.getSlope(this), other.getSlope(other)))) {
            //checks if starts or ends Points of the lines are equals.
            if (this.start.equals(other.end) || this.end.equals(other.start)) {
                return true;
            }
        }
        if (this.intersectionWith(other) != null) {
            return true;
        }
        return false;
    }
    /**
     * the method calculate the equation of the two lines and find with it the intersection point.
     * @param other - some line to find the intersecting Point with him.
     * @return - return Point if there is an intersection point between this object(line) to the other line.
     */
    public Point intersectionWith(Line other) {
        //variable that store the x,y value of the intersection point.
        double intersectionXValue, intersectionYValue,
                //variable that store the slope and elevate of the two lines
                slopeMyLine, slopeOtherLine, myLineElevate, otherLineElevate;
        //calculate slope and elevate for the two lines
        slopeMyLine = getSlope(this);
        slopeOtherLine = getSlope(other);
        myLineElevate = findLineElevate(this);
        otherLineElevate = findLineElevate(other);
        //calculate the x value of the intersection point.
        intersectionXValue = (otherLineElevate - myLineElevate) / (slopeMyLine - slopeOtherLine);

        //handle the case of line like : x = a.
        if (slopeMyLine == 0 && this.start.getY() != this.end.getY()) {
            intersectionXValue = this.start.getX();
            double checkY =  (slopeOtherLine * intersectionXValue) + otherLineElevate;
            if ((other.start.getY() <= checkY && other.end.getY() >= checkY)) {
                return new Point(intersectionXValue, checkY);
            }
        }
        //handle the case of the other line if he like : x = a
        if (slopeOtherLine == 0 && other.start.getY() != other.end.getY()) {
            intersectionXValue = other.start.getX();
            double checkY = (slopeMyLine * intersectionXValue) + myLineElevate;
            if ((this.start.getY() <= checkY && this.end.getY() >= checkY)) {
                return new Point(intersectionXValue, checkY);
            }
        }
        if (slopeOtherLine == 0 && doublesEquals(other.start.getY(), other.end.getY())) {
            intersectionYValue = other.end.getY();
            intersectionXValue = (intersectionYValue - findLineElevate(this)) / getSlope(this);
            //Point checkPoint = new Point(intersectionXValue, intersectionYValue);
            if (other.start.getX() <= intersectionXValue && other.end.getX() >= intersectionXValue) {
                if (this.start.getX() <= intersectionXValue && this.end.getX() >= intersectionXValue) {
                    return new Point(intersectionXValue, intersectionYValue);
                }
            }
        }
        //handle the case that my line scope = other line scope
        if (doublesEquals(this.getSlope(this), other.getSlope(other))) {
            if (this.start.equals(other.end)) {
                return new Point(this.start.getX(), this.start.getY());
            } else if (this.end.equals(other.start)) {
                return new Point(other.start.getX(), other.start.getY());
            }
        }
        //checks if the point between the start and the end points of both of the lines.
        intersectionYValue = (intersectionXValue * slopeMyLine) + myLineElevate;
        if (intersectionXValue >= this.start.getX() && intersectionXValue <= this.end.getX()) {
            if (intersectionXValue >= other.start.getX() && intersectionXValue <= other.end.getX()) {
                return new Point(intersectionXValue, intersectionYValue);
            }
        }
        return null;
    }
    /**
     * the method calculate for us the scope of a line.
     * @param line1 - some line.
     * @return - return the Line scope.
     */
    public double getSlope(Line line1) {
        if (doublesEquals(line1.start.getX(), line1.end.getX())
                || doublesEquals(line1.start.getY(), line1.end.getY())) {
            return 0;
        }
        return (line1.start.getY() - line1.end.getY()) / (line1.start.getX() - line1.end.getX());
    }
    /**
     * the method calculate for us the elevate of a line.
     * @param line1 - some line.
     * @return the line elevate.
     */
    public double findLineElevate(Line line1) {
        return (line1.start.getY() - (getSlope(line1) * line1.start.getX()));
    }
    /**
     * checks by epsilon if x1-x2 < epsilon. if it is, the points are equals.
     * @param other - some line.
     * @return - return true if the two lines are the same line.
     */
    public boolean equals(Line other) {
        if (doublesEquals(this.start.getX(), other.start.getX())
                && doublesEquals(this.start.getY(), other.start.getY())) {
            if (doublesEquals(this.end.getX(), other.end.getX())
                    && doublesEquals(this.end.getY(), other.end.getY())) {
                return true;
            }
        }
        return false;
    }
    /**
     *the function rule is to get the closes collision point of the trajectory with some block.
     * @param rect some rectangle to check if the ball trajectory is intersect with it.
     * @return return null if no intersections or the closes intersection point to the start of the trajectory.
     */
    public Point closestIntersectionToStartOfLine(Rectangle rect) {
        List<Point> newArray =  rect.intersectionPoints(this);
        //if array empty there is no collision.
        if (newArray.isEmpty()) {
            return null;
        }
        //if there is only 1 points we return it.
        if (newArray.size() == 1) {
            return newArray.get(0);
        }
        //find the points with the minimum distance.
        return findMinDistance(newArray);
    }
    /**
     * the function rule is to find the collison Point with the minimum distance to the ball
       trajectory.
     * @param newArray - array of collision Points between the ball to
     *                 blocks that in the same game enviorment.
     *
     * @return - return value is the firs point that we going to collide with.
     */
    public Point findMinDistance(List<Point> newArray) {
        //define some minimum value.
        Point minDisPoint = newArray.get(0);
        //if there is 1 point its the minimum
        if (newArray.size() == 1) {
            return minDisPoint;
        }
        int i = 1;
        //check by a while loop the minimum distance.
        while (i < newArray.size()) {
            if (this.end.distance(newArray.get(i)) <= this.end.distance(minDisPoint)) {
                minDisPoint = newArray.get(i);
            }
            i++;
        }
        return minDisPoint;
    }
    /**
     * the function get a Point and checks if the point inside this line.
       if the point inside this line we return true.
     * @param checkPoint - some point to check .
     * @return true/false
     */
    public boolean ifPointInLine(Point checkPoint) {
        double maxXValue = (Math.max(this.start.getX(), this.end.getX()));
        double minXValue = (Math.min(this.start.getX(), this.end.getX()));
        //checks if the point inside line of the kind: x = a.
        if (doublesEquals(this.end.getX(), this.start.getX())) {
            if (checkPoint.getY() >= this.start.getY() && checkPoint.getY() <= this.end.getY()) {
                if (checkPoint.getX() <= this.end.getX() && checkPoint.getX() >= this.start.getX()) {
                    return true;
                }
            }
        }
        //checks if the point inside line of the kind: y = a;
        if (doublesEquals(this.start.getY(), this.end.getY())) {
            if (((checkPoint.getX() >= minXValue) && (checkPoint.getX() <= maxXValue))) {
                return doublesEquals(checkPoint.getY(), this.end.getY());
            }
        }
        if (checkPoint.getX() <= this.end.getX() && checkPoint.getX() >= this.start.getX()) {
            return checkPoint.getY() <= this.end.getY() && checkPoint.getY() >= this.start.getY();
        }
        return false;


    }
    /**
     *the function compare betweem 2 doubles by epsilon for more precision.
     * @param x1 - some double
     * @param y1 - some double
     * @return true/false
     */
    public boolean doublesEquals(double x1, double y1) {
        double epsilon = Math.pow(10, -2);
        return Math.abs(x1 - y1) < epsilon;
    }
}
