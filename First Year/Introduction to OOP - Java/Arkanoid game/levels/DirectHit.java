package levels;
import geometry.Point;
import geometry.Rectangle;
import interfaces.LevelInformation;
import interfaces.Sprite;
import sprites.Block;
import supportobjects.Velocity;
import java.awt.Color;
import java.util.ArrayList;
import java.util.List;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class DirectHit implements LevelInformation {
    /**+
     * no need for constructor.
     */
    public DirectHit() {
    }
    @Override
    public int numberOfBalls() {
        return 1;
    }
    @Override
    public List<Velocity> initialBallVelocities() {
        List<Velocity> list = new ArrayList<>();
        list.add(new Velocity(0, -10));
        return list;
    }
    @Override
    public int paddleSpeed() {
        return 10;
    }
    @Override
    public int paddleWidth() {
        return 100;
    }
    @Override
    public String levelName() {
        return "Direct Hit";
    }
    @Override
    public Sprite getBackground() {
       return new Block(new Rectangle(new Point(0, 0), 800, 600), Color.BLACK);
    }
    @Override
    public List<Block> blocks() {
        List<Block> list = new ArrayList<>();
        list.add(new Block(new Rectangle(new Point(385, 120), 30, 30), Color.RED));
        return list;
    }
    @Override
    public int numberOfBlocksToRemove() {
        return 1;
    }
}
