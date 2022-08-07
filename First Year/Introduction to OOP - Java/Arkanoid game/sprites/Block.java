package sprites;
import java.awt.Color;
import java.util.ArrayList;
import java.util.List;

import animation.GameLevel;
import biuoop.DrawSurface;
import geometry.Rectangle;
import interfaces.Collidable;
import interfaces.HitListener;
import interfaces.HitNotifier;
import interfaces.Sprite;
import supportobjects.Velocity;
import geometry.Point;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class Block implements Collidable, Sprite, HitNotifier {
    /**
     *block class implements Collidable interface and the Sprite interface
     * this class generate blocks object for the game.
     */
    private final List<HitListener> hitListeners;
    private final Rectangle blockInform;
    private Color color;

    /**
     *constructor that initialize all the field for the new object.
     * @param newBlock - an rectangle object that we define the new block with it.
     */
    public Block(Rectangle newBlock) {
        this.blockInform = newBlock;
        this.color = this.blockInform.getColor();
        this.hitListeners = new ArrayList<>();
    }
    /**
     *another constructor that also can get a color and using the original object for the other field.
     * @param newBlock - an rectangle object that we define the new block with it.
     * @param color - color for the block
     */
    public Block(Rectangle newBlock, Color color) {
        this(newBlock);
        this.color = color;
    }
    /**
     *get an access to the field out side the class.
     * @return the field blockInform (the rectangle that describe this block).
     */
    @Override
    public Rectangle getCollisionRectangle() {
        return this.blockInform;
    }
    /**
     * the function check in which side of the rectangle the collision point,
       amd accordingly changing the current velocity and return new one.
     * @param collisionPoint - the point that we check in which side of the block its found.
     * @param currentVelocity - the velocity that we want to change accordingly the location of the collision point.
     * @param hitter - the hitter ball in the current collision.
     * @return the new velocity.
     */
    @Override
    public Velocity hit(Ball hitter, Point collisionPoint, Velocity currentVelocity) {
        notifyHit(hitter);
        double newDx = currentVelocity.getDx();
        double newDy = currentVelocity.getDy();
        if ((this.blockInform.getDownYLine().ifPointInLine(collisionPoint) && (newDy < 0)
                || (this.blockInform.getUpYLine().ifPointInLine(collisionPoint)))) {
            //changing the dy.
            newDy = -newDy;
            return new Velocity(newDx, newDy);
        }
        //checks if the collision point on the left or right line of the block.
        if ((this.blockInform.getLeftXLine().ifPointInLine(collisionPoint) && (newDx > 0))
                || (this.blockInform.getRightXLine().ifPointInLine(collisionPoint))) {
            //changing the dx.
            newDx = -newDx;
            return new Velocity(newDx, newDy);
        }
        //return the new velocity.
        return new Velocity(newDx, newDy);
    }
    /**
     *the function draw on the given surface the require block.
     * @param surface - the surface we want to draw the block on it.
     */
    @Override
    public void drawOn(DrawSurface surface) {
        double collideX = this.blockInform.getUpperLeft().getX();
        double collideY = this.blockInform.getUpperLeft().getY();
        surface.setColor(this.color);
        surface.fillRectangle((int) collideX, (int) collideY,
                (int) blockInform.getWidth(), (int) blockInform.getHeight());
        surface.setColor(Color.black);
        surface.drawRectangle((int) collideX, (int) collideY,
                (int) blockInform.getWidth(), (int) blockInform.getHeight());
    }
    /**
     *not using the function for now, but the function rule is to notify the blocks to do an action,
      means maybe to change color or to disappear when ball hits the block.
     */
    @Override
    public void timePassed() {
    }
    /**
     *the function add the block to the arrays that store the objects of the game.
     * @param g - the game that we want to had the block to his(game) objects arrays.
     */
    public void addToGame(GameLevel g) {
        g.addCollidable(this);
        g.addSprite(this);
    }

    /**
     * the function removing the block from the game.
     * doing that by removing the blocks from Collidable collection and from Sprite collection.
     * @param game - the game we want to remove the block from.
     */
    public void removeFromGame(GameLevel game) {
        game.removeCollidable(this);
        game.removeSprite(this);
    }

    /**
     * to be able to remove the block only from Sprite collection,
       as we do with the "death region" block that under the paddle.
     * @param game - the game we want to remove the block from.
     */
    public void removeFromSprite(GameLevel game) {
        game.removeSprite(this);
    }
    @Override
    public void addHitListener(HitListener hl) {
        this.hitListeners.add(hl);
    }
    @Override
    public void removeHitListener(HitListener hl) {
        this.hitListeners.remove(hl);
    }

    /**
     * the function notify about an hit and call hitevent in blockremover.
     * @param hitter - the hitter ball.
     */
    private void notifyHit(Ball hitter) {
        // Make a copy of the hitListeners before iterating over them.
        List<HitListener> listeners = new ArrayList<>(this.hitListeners);
        // Notify all listeners about a hit event:
        for (HitListener hl : listeners) {
            hl.hitEvent(this, hitter);
        }
    }
}



