package interfaces;
import sprites.Block;
import supportobjects.Velocity;
import java.util.List;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public interface LevelInformation {
    /**
     * method that define the number of the balls in the level.
     * @return number of balls.
     */
    int numberOfBalls();
    //
    // Note that initialBallVelocities().size() == numberOfBalls()

    /**
     * The initial velocity of each ball.
     * @return list of velocities.
     */
    List<Velocity> initialBallVelocities();

    /**
     * method that define the paddle speed in the level.
     * @return the paddle speed.
     */
    int paddleSpeed();

    /**
     * method that define the paddle width in the level.
     * @return the paddle width.
     */
    int paddleWidth();
    // the level name will be displayed at the top of the screen.
    /**
     * method that define the name level that will show on the screen during the game.
     * @return the level name.
     */
    String levelName();

    /**
     * method that generate the background of the level.
     * @return a sprite with the background of the level.
     */
    Sprite getBackground();

    /**
     * The Blocks that make up this level, each block contains its size, color and location.
     * @return list of blocks in the specific level.
     */
    List<Block> blocks();

    /**
     * Number of blocks that should be removed before the level is considered to be "cleared".
     * @return the number of blocks to remove.
     */
    int numberOfBlocksToRemove();
}
