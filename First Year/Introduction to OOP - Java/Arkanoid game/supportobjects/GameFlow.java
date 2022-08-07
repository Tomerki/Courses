package supportobjects;
import animation.AnimationRunner;
import animation.EndScreen;
import animation.GameLevel;
import animation.KeyPressStoppableAnimation;
import interfaces.LevelInformation;
import java.util.List;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class GameFlow {
    private final AnimationRunner runner;
    private final Counter score;
    private final Counter lives;

    /**
     * constructor that initialize new GameFlow object with the given parameters.
     * @param ar - the variable that points on the objects that describe the level of the game
     *           we want to run.
     */
    public GameFlow(AnimationRunner ar) {
        this.runner = ar;
        this.score = new Counter(0);
        this.lives = new Counter(7);
    }

    /**
     * the methods runs the level according the order of the levels in the given list.
     * @param levels - the list that indicate the order of the levels in the game.
     */
    public void runLevels(List<LevelInformation> levels) {
        int count = 0;
        for (LevelInformation levelInfo : levels) {
            count++;
            GameLevel level = new GameLevel(levelInfo, this.runner, this.score, this.lives);
            level.initialize();
            while (level.getNumberOfBlocks().getValue() != 0 && level.getNumberOfBalls().getValue() != 0) {
                level.run();
                if (level.getNumberOfBalls().getValue() == 0 && this.lives.getValue() > 0) {
                    this.lives.decrease(1);
                    if (this.lives.getValue() == 0) {
                        this.runner.run(new KeyPressStoppableAnimation(this.runner.getGui().getKeyboardSensor(),
                                "space", new EndScreen(level.getNumberOfBlocks().getValue(),
                                this.score.getValue())));
                        this.runner.getGui().close();
                    }
                    level.setPaddleLocation();
                    level.generateBalls();
                    level.setCounterBalls(level.getLevelInfo().numberOfBalls());
                }
            }
            if (count == levels.size()) {
                this.runner.run(new KeyPressStoppableAnimation(this.runner.getGui().getKeyboardSensor(),
                        "space", new EndScreen(level.getNumberOfBlocks().getValue(),
                        this.score.getValue())));
                this.runner.getGui().close();
            }
        }
    }
}
