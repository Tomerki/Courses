package listeners;

import animation.GameLevel;
import interfaces.HitListener;
import sprites.Ball;
import sprites.Block;
import supportobjects.Counter;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class BallRemover implements HitListener {
    //field of the current game that we counting the balls in it.
    private final GameLevel game;
    //field of Counter class.
    private final Counter remainingBalls;
    /**
     * constructor creating an object that responsible on removing balls to the game and count them.
     * @param game - the current game object.
     * @param numberOfBalls - number of balls in this game.
     */
    public BallRemover(GameLevel game, Counter numberOfBalls) {
        this.game = game;
        this.remainingBalls = numberOfBalls;
    }
    @Override
    public void hitEvent(Block beingHit, Ball hitter) {
        hitter.removeFromGame(this.game);
        this.remainingBalls.decrease(1);
    }
}
