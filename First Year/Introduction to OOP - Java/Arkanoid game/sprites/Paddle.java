package sprites;
import animation.GameLevel;
import biuoop.DrawSurface;
import biuoop.KeyboardSensor;
import geometry.Point;
import geometry.Rectangle;
import interfaces.Collidable;
import interfaces.Sprite;
import supportobjects.Velocity;

import java.awt.Color;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class Paddle implements Collidable, Sprite {
    static final int PART_OF_PADDLE = 20;
    static final int ANGLE_REGION_ONE = 300;
    static final int ANGLE_REGION_TWO = 330;
    static final int ANGLE_REGION_FOUR = 30;
    static final int ANGLE_REGION_FIVE = 60;


    private Rectangle thePaddle;
    private final KeyboardSensor keyboard;
    private double myPaddleSpeed;

    /**
     * constructor that initialize the field for the new object with the require value.
     * @param paddle - the rectangle that we use to generate the paddle object.
     * @param keyboard - an object that help us know if the user want to move the paddle to some side.
     */
    public Paddle(Rectangle paddle, KeyboardSensor keyboard) {
        this.thePaddle = new Rectangle(paddle.getUpperLeft(), paddle.getWidth(), paddle.getHeight(), paddle.getColor());
        this.keyboard = keyboard;
        this.myPaddleSpeed = paddle.getWidth();
    }
    /**
     * function checks if the user want to move left with the paddle.
     * the paddle move 8 units each press so we check if the distance from the blocks bounderies is less then 8.
     * if the distance is lower than 8 we just set the paddle to go to the leftest point he can go.
     */
    public void moveLeft() {
        Point newLocation = new Point(thePaddle.getUpperLeft().getX()
                - this.myPaddleSpeed, thePaddle.getUpperLeft().getY());
        //if the distance is more than 8 we simply move 10 units to the left.
        if (thePaddle.getUpperLeft().distance(new Point(40, thePaddle.getUpperLeft().getY())) > this.myPaddleSpeed) {
            this.thePaddle = new Rectangle(newLocation, thePaddle.getWidth(),
                    thePaddle.getHeight(), this.thePaddle.getColor());
            //if the distance less than 10 we just set the leftest location we can.
        } else {
            this.thePaddle = new Rectangle(new Point(40, thePaddle.getUpperLeft().getY()),
                    thePaddle.getWidth(), thePaddle.getHeight(), this.thePaddle.getColor());
        }
    }
    /**
     * function checks if the user want to move right with the paddle.
     * the paddle move 8 units each press so we check if the distance from the blocks bounderies is less then 8.
     * if the distance is lower than 8 we just set the paddle to go to the rightest point he can go.
     */
    public void moveRight() {
        Point newLocation = new Point(thePaddle.getUpperLeft().getX() + this.myPaddleSpeed,
                thePaddle.getUpperLeft().getY());
        //if the distance is more than 8 we simply move 10 units to the right.
        if (thePaddle.getUpperRight().distance(new Point(760,
                thePaddle.getUpperRight().getY())) > this.myPaddleSpeed) {
            this.thePaddle = new Rectangle(newLocation, thePaddle.getWidth(),
                    thePaddle.getHeight(), this.thePaddle.getColor());
        //else if the distance less than 10 we just set the rightest location we can.
        } else {
            this.thePaddle = new Rectangle(new Point(760 - this.thePaddle.getWidth(),
                    thePaddle.getUpperLeft().getY()),
                    thePaddle.getWidth(), thePaddle.getHeight(), this.thePaddle.getColor());
        }
    }
    /**
     * checks whick size the user want to move and call moveleft/right methods accordingly.
     */
    @Override
    public void timePassed() {
        if (keyboard.isPressed(KeyboardSensor.LEFT_KEY)) {
            this.moveLeft();
        }
        if (keyboard.isPressed(KeyboardSensor.RIGHT_KEY)) {
            this.moveRight();
        }
    }
    /**
     *the function draw the paddle on the given surface.
     * @param d - surface to draw on
     */
    @Override
    public void drawOn(DrawSurface d) {
        d.setColor(this.thePaddle.getColor());
        d.fillRectangle((int) thePaddle.getUpperLeft().getX(), (int) thePaddle.getUpperLeft().getY(),
                (int) thePaddle.getWidth(), (int) thePaddle.getHeight());
        d.setColor(Color.black);
        d.drawRectangle((int) thePaddle.getUpperLeft().getX(), (int) thePaddle.getUpperLeft().getY(),
                (int) thePaddle.getWidth(), (int) thePaddle.getHeight());
    }

    /**
     * get the paddle information - to have an access out of the class.
     * @return the rectangle that we use to create a new paddle.
     */
    @Override
    public Rectangle getCollisionRectangle() {
        return this.thePaddle;
    }
    /**
     * the function return a new velocity according the part that the ball hit the paddle.
     * @param collisionPoint - point that we check its location on the paddle.
     * @param currentVelocity - the velocity that we need to change accordingly
     *                        the collisionPoint location on the paddle.
     * @param hitter - parameter that we get because we have to, but doesnt have any use.
     * @return the new velocity after we change the current velocity.
     */
    @Override
    public Velocity hit(Ball hitter, Point collisionPoint, Velocity currentVelocity) {
        double newDx = currentVelocity.getDx();
        double newDy = currentVelocity.getDy();
        //calculate the new speed of the ball.
        double newSpeed = getNewSpeed(currentVelocity);
        //define the points that with them we can divide the paddle to five regions.
        double pointOne = (this.thePaddle.getUpperLeft().getX() + PART_OF_PADDLE);
        double pointTwo = (pointOne + PART_OF_PADDLE);
        double pointThree = (pointTwo + PART_OF_PADDLE);
        double pointFour = (pointThree + PART_OF_PADDLE);
        Velocity v = currentVelocity;
        //checks if the collision point on the sides of the paddle.
        if (collisionPoint.getY() >= this.getCollisionRectangle().getUpperLeft().getY()
                && collisionPoint.getY() <= this.getCollisionRectangle().getLowerLeft().getY()) {
            if ((this.getCollisionRectangle().getLeftXLine().ifPointInLine(collisionPoint) && newDx >= 0)
                    || (this.getCollisionRectangle().getRightXLine().ifPointInLine(collisionPoint) && newDx <= 0)) {
                newDx *= -1;
                return new Velocity(Math.round(newDx), Math.round(newDy));
            }
        }
        //checks if the point on region one
        if (collisionPoint.getX() > this.thePaddle.getUpperLeft().getX() && collisionPoint.getX() < pointOne) {
            v = Velocity.fromAngleAndSpeed(ANGLE_REGION_ONE, newSpeed);
            return new Velocity(Math.round(v.getDx()), Math.round(v.getDy()));
        }
        //checks if the point on region two
        if ((collisionPoint.getX() > pointOne) && collisionPoint.getX() < pointTwo) {
            v = Velocity.fromAngleAndSpeed(ANGLE_REGION_TWO, newSpeed);
            return new Velocity(Math.round(v.getDx()), Math.round(v.getDy()));
        }
        //checks if the point on region three
        if ((collisionPoint.getX() > pointTwo && collisionPoint.getX() < pointThree)) {
            newDy *= -1;
            return new Velocity(Math.round(newDx), Math.round(newDy));
        }
        //checks if the point on region four
        if ((collisionPoint.getX() > pointThree && collisionPoint.getX() < pointFour)) {
            v = Velocity.fromAngleAndSpeed(ANGLE_REGION_FOUR, newSpeed);
            return new Velocity(Math.round(v.getDx()), Math.round(v.getDy()));
        }
        //checks if the point on region five
        if (collisionPoint.getX() > pointFour && collisionPoint.getX() < this.thePaddle.getUpperRight().getX()) {
            v = Velocity.fromAngleAndSpeed(ANGLE_REGION_FIVE, newSpeed);
            return new Velocity(Math.round(v.getDx()), Math.round(v.getDy()));
        }
        return new Velocity(Math.round(v.getDx()), Math.round(v.getDy()));
    }

    /**
     *add the paddle to the arrays that hold the objects of the game.
     * @param g the game that we want to add the paddle to his objects arrays.
     */
    public void addToGame(GameLevel g) {
        g.addSprite(this);
        g.addCollidable(this);
    }
    /**
     * calculate the new speed for sending it to fromAngleAndSpeed method.
     * @param currentVelocity - the velocity that we calculate the speed with it.
     * @return the result speed from the current dx,dy.
     */
    public double getNewSpeed(Velocity currentVelocity) {
        //using pythagoras formula.
        return Math.sqrt(Math.pow(currentVelocity.getDx(), 2) + Math.pow(currentVelocity.getDy(), 2));
    }

    /**
     * method that set the paddle speed.
     * @param speed - the new speed of the paddle.
     */
    public void setPaddleSpeed(int speed) {
        this.myPaddleSpeed = speed;
    }
}
























