package listeners;

import animation.GameLevel;
import interfaces.HitListener;
import sprites.Ball;
import sprites.Block;
import supportobjects.Counter;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class BlockRemover implements HitListener {

    private final GameLevel game;
    private final Counter remainingBlocks;

    /**
     * constructor creating an object that responsible on removing blocks to the game and count them.
     * @param game - the current game.
     * @param numberOfBlocks - the number of the blocks in the current game.
     */
    public BlockRemover(GameLevel game, Counter numberOfBlocks) {
        this.game = game;
        this.remainingBlocks = numberOfBlocks;
    }
    @Override
    public void hitEvent(Block beingHit, Ball hitter) {
        beingHit.removeFromGame(this.game);
        this.remainingBlocks.decrease(1);
        if (this.remainingBlocks.getValue() == 0) {
            this.game.getScore().increase(100);
        }
    }
}
