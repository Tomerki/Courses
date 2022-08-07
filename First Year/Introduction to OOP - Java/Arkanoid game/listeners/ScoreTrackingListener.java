package listeners;

import interfaces.HitListener;
import sprites.Ball;
import sprites.Block;
import supportobjects.Counter;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class ScoreTrackingListener implements HitListener {

    private final Counter currentScore;

    /**
     * constructor that creating an object that tracking the score in the game according to the player achievements.
     * @param scoreCounter - parameter of Counter class that holds score of the player.
     */
    public ScoreTrackingListener(Counter scoreCounter) {
        this.currentScore = scoreCounter;
    }
    @Override
    public void hitEvent(Block beingHit, Ball hitter) {
        this.currentScore.increase(5);

    }
}
