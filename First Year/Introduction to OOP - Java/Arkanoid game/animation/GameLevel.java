package animation;
import biuoop.DrawSurface;
import geometry.Point;
import geometry.Rectangle;
import interfaces.Collidable;
import interfaces.LevelInformation;
import interfaces.Sprite;
import listeners.BallRemover;
import listeners.BlockRemover;
import listeners.ScoreTrackingListener;
import sprites.Block;
import sprites.Ball;
import sprites.Paddle;
import sprites.ScoreIndicator;
import sprites.SpriteCollection;
import sprites.StringsInGame;
import supportobjects.Counter;
import supportobjects.GameEnvironment;
import java.awt.Color;
import java.util.List;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class GameLevel implements Animation {
    /**
     * Game class rule is to initialize anew game and all the object that we need for a new game.
     */
    static final int START_X_VALUE = 400;
    static final int START_Y_VALUE = 550;
    static final int BALLS_RADIUS = 5;
    static final int BLOCKS_HEIGHT = 20;

    private final SpriteCollection sprites;
    private final GameEnvironment environment;
    private final Counter countBlocks;
    private final Counter countBalls;
    private final Counter score;
    private final Counter lives;
    private final AnimationRunner runner;
    private boolean running;
    private final LevelInformation theLevel;
    private final Paddle myPaddle;


    /**
     * constructor that create a game according the level information.
     * @param myLevel - the level we want its information.
     * @param runner - object that run the game.
     * @param score - the score of the game, pass as argument because we dont want that every level
     *              the score restart
     * @param lives - the number of life in the game.
     */
    public GameLevel(LevelInformation myLevel, AnimationRunner runner, Counter score, Counter lives) {
        this.theLevel = myLevel;
        this.sprites = new SpriteCollection();
        this.environment = new GameEnvironment();
        this.countBlocks = new Counter(this.theLevel.blocks().size());
        this.countBalls = new Counter(this.theLevel.numberOfBalls());
        this.score = score;
        this.runner = runner;
        this.lives = lives;
        this.myPaddle = new Paddle(new Rectangle(new Point(100, 560), this.theLevel.paddleWidth(),
                BLOCKS_HEIGHT), this.runner.getGui().getKeyboardSensor());
    }

    /**
     *the function add to the array a new object that we can callide with and initialize it in the game class.
     * @param c - a collidable variable the point on an object that we want to add to the collidable array in the
     *         environment.
     */
    public void addCollidable(Collidable c) {
        this.environment.addCollidable(c);
    }
    /**
     *the function add to the sprite array a new object that we can collide with and initialize it in the game class.
     * @param s - a sprite variable the point on an object that we want to add to the sprite array in the
     *          environment.
     */
    public void addSprite(Sprite s) {
        this.sprites.addSprite(s);
    }
    // Initialize a new game: create the Blocks and Ball (and Paddle)
    // and add them to the game.

    /**
     *function initialize all the object that we need for new game by calling other helps function.
     */
    public void initialize() {
        //initialize the boundries blocks
        generateBoundriesBlocks();
        //initialize paddle and add him
        setPaddle();
        //initialize balls.
        generateBalls();
        //initialize the blocks in the game.
        generateBlocksGame();
        ScoreIndicator scoreScreen = new ScoreIndicator(this.score);
        StringsInGame str = new StringsInGame(this);
        sprites.addSprite(scoreScreen);
        sprites.addSprite(str);
    }
    // Run the game -- start the animation loop.
    /**
     *function that run the game after we initialize all the things we need.
     */
    public void run() {
        this.runner.run(new CountdownAnimation(2, 3, this.sprites));
        // use our runner to run the current animation -- which is one turn of
        // the game.
        this.running = true;
        this.runner.run(this);
    }

    /**
     *
     */
    public void setPaddle() {
        double w = (double) (this.runner.getGui().getDrawSurface().getWidth() / 2)
                - (double) (this.theLevel.paddleWidth() / 2);
        this.myPaddle.getCollisionRectangle().setUpperLeft(new Point(w, 560));
        this.myPaddle.getCollisionRectangle().setColor(Color.yellow);
        this.myPaddle.setPaddleSpeed(this.theLevel.paddleSpeed());
        this.myPaddle.addToGame(this);
    }

    /**
     *
     */
    public void setPaddleLocation() {
        double w = (double) (this.runner.getGui().getDrawSurface().getWidth() / 2)
                - (double) (this.theLevel.paddleWidth() / 2);
        this.myPaddle.getCollisionRectangle().setUpperLeft(new Point(w, 560));
    }
    /**
     *initialize the blocks that define the balls boundries.
     */
    public void generateBoundriesBlocks() {
        BallRemover removeBall = new BallRemover(this, countBalls);
        Block top = new Block(new Rectangle(new Point(40, 0), 720, 30), Color.white);
        Block down = new Block(new Rectangle(new Point(40, 570), 760, 30), Color.gray);
        Block right = new Block(new Rectangle(new Point(0, 0), 40, 600), Color.gray);
        Block left = new Block(new Rectangle(new Point(760, 0), 40, 600), Color.gray);
        //add the background to the sprites.
        this.sprites.addSprite(this.theLevel.getBackground());
        //add all the blocks to the game.
        right.addToGame(this);
        left.addToGame(this);
        top.addToGame(this);
        down.addToGame(this);
        down.removeFromSprite(this);
        down.addHitListener(removeBall);

    }
    /**
     *initialize balls for the game and set them a velocity, and gameEnvironment, after that add them to the game.
     */
    public void generateBalls() {
        for (int i = 0; i < this.theLevel.numberOfBalls(); i++) {
            Ball ball = new Ball(new Point(START_X_VALUE, START_Y_VALUE), BALLS_RADIUS, Color.white);
            ball.setVelocity(this.theLevel.initialBallVelocities().get(i));
            ball.setGameEnvironment(this.environment);
            ball.addToGame(this);
        }
    }
    /**
     *initialize the blocks that in the game.
     */
    public void generateBlocksGame() {
        List<Block> blocksList = this.theLevel.blocks();
        BlockRemover removal = new BlockRemover(this, countBlocks);
        ScoreTrackingListener scoreTracking = new ScoreTrackingListener(score);
        for (Block b : blocksList) {
            b.addToGame(this);
            b.addHitListener(removal);
            b.addHitListener(scoreTracking);
        }
    }

    /**
     * function to remove an collidable object from the game.
     * @param c - the variable that point the object we want to remove.
     */
    public void removeCollidable(Collidable c) {
        this.environment.getCollidableList().remove(c);
    }

    /**
     * function to remove Sprite object from the game.
     * @param s - the variable that point the object we want to remove.
     */
    public void removeSprite(Sprite s) {
        this.sprites.getSpriesArray().remove(s);
    }
    @Override
    public void doOneFrame(DrawSurface d) {
        this.sprites.drawAllOn(d);
        //notify the object to do there move.
        this.sprites.notifyAllTimePassed();
        if (this.countBlocks.getValue() == 0) {
            this.running = false;
        }
        if (this.countBalls.getValue() == 0) {
            this.running = false;
        }

        if (this.runner.getGui().getKeyboardSensor().isPressed("p")) {
            this.runner.run(new KeyPressStoppableAnimation(this.runner.getGui().getKeyboardSensor(),
                    "space", new PauseScreen()));
        }
    }
    @Override
    public boolean shouldStop() {
        return !this.running;
    }

    /**
     * getter for the score in the game.
     * @return the Counter score.
     */
    public Counter getScore() {
        return this.score;
    }

    /**
     *  getter for the number of the blocks.
     * @return the Counter of the blocks.
     */
    public Counter getNumberOfBlocks() {
        return this.countBlocks;
    }

    /**
     * getter for number of balls.
     * @return Counter of balls.
     */
    public Counter getNumberOfBalls() {
        return this.countBalls;
    }

    /**
     * getter fot the level information.
     * @return the variable of levelInformation that point on some level.
     */
    public LevelInformation getLevelInfo() {
        return this.theLevel;
    }

    /**
     * getter for the lives counter.
     * @return Counter of lives.
     */
    public Counter getLives() {
        return this.lives;
    }

    /**
     * method that set the number of the balls in the game.
     * @param number - the number of balls in the game.
     */
    public void setCounterBalls(int number) {
        this.countBalls.setValue(number);
    }
}
