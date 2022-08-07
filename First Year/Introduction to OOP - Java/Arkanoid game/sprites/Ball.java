package sprites;
import animation.GameLevel;
import biuoop.DrawSurface;
import geometry.Line;
import geometry.Point;
import interfaces.Sprite;
import supportobjects.CollisionInfo;
import supportobjects.GameEnvironment;
import supportobjects.Velocity;
import java.awt.Color;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class Ball implements Sprite {
    /**
     * ball class create balls(circiles) object.
     * and implements an interface.
     */
    //fields - center point of the circle
    private Point center;
    //circle size
    private int radius;
    //circle color.
    private final java.awt.Color color;
    //ball velocity
    private Velocity ballVelocity;
    //board limits
    private  Point boardMaxLimits, boardMinLimits;
    private GameEnvironment myGame;
    /**
     * constructor that initialize a new ball with minimum parameters.
     * @param center - describe the center Point of the ball
     * @param radius - the ball size
     * @param color - the ball color
     */
    public Ball(Point center, int radius, java.awt.Color color) {
        this.center = center;
        this.radius = radius;
        this.color = color;
        //fields that we use only in case we need them - we initialize them for the program safty.
        this.ballVelocity = new Velocity(0, 0);
        this.boardMaxLimits = new Point(0, 0);
        this.boardMinLimits = new Point(0, 0);
        this.myGame = new GameEnvironment();
    }
    /**
     * another constructor that handle the case that
     we get for parameters two numbers instead of a point.
     * @param x - x center point value
     * @param y - y center point value
     * @param radius - ball size
     * @param color - ball color
     */
    public Ball(int x, int y, int radius, java.awt.Color color) {
        //using the original constructor.
        this(new Point(x, y), radius, color);
    }
    /**
     * set max x,y center point value of the ball to keep the ball
     inside the frame.
     * @param hight - max y value
     * @param width - max x value
     */
    public void setMaxBallBoundaries(int hight, int width) {
        //using a point to describe the max x,y
        this.boardMaxLimits = new Point(width, hight);
    }
    /**
     * get max y center point value.
     * @return max y value of the center point.
     */
    public double getMaxBallHight() {
        return this.boardMaxLimits.getY();
    }
    /**
     * get max x center point value.
     * @return max x value of the center point.
     */
    public double getMaxBallWidth() {
        return this.boardMaxLimits.getX();
    }
    /**
     * set min x,y center point value of the ball to keep the ball.
     inside the frame.
     * @param hight - min y value
     * @param width - min x value
     */
    public void setMinBallBoundaries(int hight, int width) {
        //using a point to describe the min x,y
        this.boardMinLimits = new Point(hight, width);
    }
    /**
     * get min y center point value.
     * @return min y value of the center point.
     */
    public double getMinBallHight() {
        return this.boardMinLimits.getY();
    }
    /**
     * get min x center point value.
     * @return min x value of the center point.
     */
    public double getMinBallWidth() {
        return this.boardMinLimits.getX();
    }
    /**
     * get x value of center point.
     * @return x value of the center point
     */
    public double getX() {
        //return x value for the object that called the method.
        return this.center.getX();
    }
    /**
     * get y value of center point.
     * @return y value of the center point
     */
    public double getY() {
        //return y value for the object that called the method.
        return this.center.getY();
    }
    /**
     * get the circle radius.
     * @return circle radius
     */
    public int getSize() {
        return this.radius;
    }
    /**
     * can change the ball size during the program.
     * @param newRadius - get as argument the new size
     */
    public void setSize(int newRadius) {
        this.radius = newRadius;
    }
    /**
     * set new center for the ball.
     * @param x - new x value
     * @param y - new y value
     */
    public void setCenter(double x, double y) {
        this.center = new Point(x, y);
    }

    /**
     *function set a new center for the ball.
     * @param newCenter new point for new center
     */
    public void setCenter(Point newCenter) {
        this.center = newCenter;
    }
    /**
     * get circle color.
     * @return circle color
     */
    public java.awt.Color getColor() {
        return this.color;
    }
    /**
     * function rule is to get the GameEnvironment of the ball - to have an access out side
       of the class.
     * @return the GameEnvironment field of the ball.
     */
    public GameEnvironment getGameEnvironment() {
        return this.myGame;
    }

    /**
     * the function rule is to set the ball environment.
     * @param environment - the new environment to set for the ball.
     */
    public void setGameEnvironment(GameEnvironment environment) {
        this.myGame = environment;
    }
    /**
     * paint the ball that called the method on the surface.
     * function that ball implement from the interface sprite.
     * @param surface - surface to paint to ball on.
     */
    @Override
    public void drawOn(DrawSurface surface) {
        if (this.getSize() < 0) {
            this.setSize(-this.getSize());
        }
        if (surface.getHeight() <= (this.getSize() * 2) || surface.getWidth() <= (this.getSize() * 2)) {
            this.setSize(surface.getHeight() / 3);
        }
        surface.setColor(this.color);
        surface.fillCircle((int) this.getX(), (int) this.getY(), this.getSize());
        surface.setColor(Color.black);
        surface.drawCircle((int) this.getX(), (int) this.getY(), this.getSize());
    }
    /**
     * set ball velocity.
     * @param velocity - the new velocity of the ball
     */
    public void setVelocity(Velocity velocity) {
        this.ballVelocity = velocity;
    }
    /**
     * create a velocity for the ball.
     * @param dx - x velocity
     * @param dy - y velocity
     */
    public void setVelocity(double dx, double dy) {
        this.ballVelocity = new Velocity(dx, dy);
    }
    /**
     * get ball velocity.
     * @return the velocity of the ball that called the method.
     */
    public Velocity getVelocity() {
        return this.ballVelocity;
    }
    /**
     * the method andle the case while balls moving on the screen and hit blocks,
     so the method changing the dx/dy direction to - dx/dy.
     */
    public void moveOneStep() {
        //using epsilon for more precision.
        double epsilon = Math.pow(10, -2);
        double r1 = this.radius + epsilon;
        double r2 = this.radius + epsilon;
        ///checks the sign of dx,dy and define the epsilon accordingly.
        if (this.ballVelocity.getDx() < 0) {
            r1 *= -1;
        }
        if (this.ballVelocity.getDy() < 0) {
            r2 *= -1;
        }
        Line ballTrajectory = new Line(this.center, new Point(this.center.getX() + r1, this.center.getY() + r2));
        CollisionInfo myInfo = this.myGame.getClosestCollision(ballTrajectory);
        //checks if there is a collision point (if my info == null its mean no collision point)
        if (myInfo == null) {
            this.setCenter(this.ballVelocity.applyToPoint(this.center));
        //if there is a collision point we get new velocity from hit
        } else {
            Velocity v = myInfo.collisionObject().hit(this, myInfo.collisionPoint(), this.ballVelocity);
            this.setCenter(v.applyToPoint(this.center));
            this.setVelocity(v);
        }
    }

    /**
     * function that ball class implement .
     * the function calls moveonestep function.
     */
    @Override
    public void timePassed() {
        this.moveOneStep();
    }

    /**
     * the function add the ball to the game.
     * @param g - game object of the current game.
     */
    public void addToGame(GameLevel g) {
        g.addSprite(this);
    }

    /**
     * the function remove the ball from the sprite collection.
     * @param g - game object of the current game.
     */
    public void removeFromGame(GameLevel g) {
        g.removeSprite(this);
    }
}


















