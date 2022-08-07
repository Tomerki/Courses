package supportobjects;


import geometry.Point;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class Velocity {
    /**
     * the class generate velocity for the ball.
     */
    //fields - dy = y velocity , dx = x velocity
    private double dx, dy;
    /**
     * constructor that generate new velocity.
     * @param dx - x velocity
     * @param dy - y velocity
     */
    public Velocity(double dx, double dy) {
        //initialize the new object with values.
        this.dx = dx;
        this.dy = dy;
    }
    /**
     * constructor that handle the case of getting
     a point to describe the velocity valuse instead getting two numbers.
     * @param p - the point that contained the velocity value.
     */
    public Velocity(Point p) {
        //using the original constructor.
        this(p.getX(), p.getY());
    }
    /**
     * method that function like a constructor and describe.
     the velocity in terms of angle and speed, and with those value
     the method calculate the dx,dy
     * @param angle - the angle accully describe the direction of the ball
     * @param speed - the speed describe the dx size
     * @return - return the new velocity.
     */
    public static Velocity fromAngleAndSpeed(double angle, double speed) {
        double dx = speed * Math.sin(Math.toRadians(angle));
        double dy = speed * (-Math.cos(Math.toRadians(angle)));
        return new Velocity(dx, dy);
    }
    /**
     * get the x velocity (dx).
     * @return x velocity
     */
    public double getDx() {
        return this.dx;
    }
    /**
     * get the y velocity (dy).
     * @return y velocity
     */
    public double getDy() {
        return this.dy;
    }
    /**
     * method that move the ball according his velocity,
     dx + x for new x value and dy+y for new y value.
     * @param p - the original point that we want to change
     * @return the new point after we promote the x/y according dx/dy.
     */
    public Point applyToPoint(Point p) {
        return new Point(p.getX() + this.dx, p.getY() + this.dy);
    }
}


