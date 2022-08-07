package interfaces;

import sprites.Ball;
import sprites.Block;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public interface HitListener {
    // This method is called whenever the beingHit object is hit.
    // The hitter parameter is the Ball that's doing the hitting.

    /**
     * This method is called whenever the beingHit object is hit.
     * @param beingHit - the beingHit object that getting hit.
     * @param hitter - The hitter parameter is the Ball that's doing the hitting.
     */
    void hitEvent(Block beingHit, Ball hitter);
}
