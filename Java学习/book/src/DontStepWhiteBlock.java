import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Random;

/**
 * 基于Swing的简化版「别踩白块」小游戏（慢速度版）
 */
public class DontStepWhiteBlock extends JFrame {
    // 游戏核心参数
    private static final int ROWS = 6;       // 显示的行数
    private static final int COLS = 4;       // 列数
    private static final int BLOCK_WIDTH = 100; // 方块宽度
    private static final int BLOCK_HEIGHT = 80; // 方块高度

    private JPanel gamePanel;                // 游戏主面板
    private JButton[][] blocks;              // 存储所有方块按钮
    private int score = 0;                   // 当前分数
    private JLabel scoreLabel;               // 分数显示标签
    private Timer gameTimer;                 // 游戏定时器（控制方块滚动）
    private int speedLevel = 300;            // 【修改1：初始间隔从100→300毫秒，慢3倍】
    private Random random = new Random();    // 随机生成黑块位置

    public DontStepWhiteBlock() {
        // 初始化窗口
        initFrame();
        // 初始化游戏面板
        initGamePanel();
        // 初始化分数面板
        initScorePanel();
        // 初始化定时器
        initTimer();
    }

    /**
     * 初始化窗口基本属性
     */
    private void initFrame() {
        setTitle("别踩白块 - Swing版（慢速度）");
        setSize(COLS * BLOCK_WIDTH, (ROWS + 1) * BLOCK_HEIGHT); // 留一行显示分数
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null); // 窗口居中
        setLayout(new BorderLayout()); // 整体布局：上下结构
        setResizable(false); // 禁止调整窗口大小
    }

    /**
     * 初始化分数显示面板（顶部）
     */
    private void initScorePanel() {
        JPanel scorePanel = new JPanel();
        scorePanel.setBackground(Color.LIGHT_GRAY);
        scoreLabel = new JLabel("分数：0");
        scoreLabel.setFont(new Font("宋体", Font.BOLD, 20));
        scorePanel.add(scoreLabel);
        add(scorePanel, BorderLayout.NORTH);
    }

    /**
     * 初始化游戏面板（中间，网格布局存放方块）
     */
    private void initGamePanel() {
        gamePanel = new JPanel();
        gamePanel.setLayout(new GridLayout(ROWS, COLS)); // 网格布局：ROWS行COLS列
        blocks = new JButton[ROWS][COLS];

        // 初始化所有方块
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                JButton block = new JButton();
                block.setFont(new Font("宋体", Font.PLAIN, 1)); // 隐藏按钮默认文字
                blocks[i][j] = block;

                // 给每个方块添加点击事件
                block.addMouseListener(new MouseAdapter() {
                    @Override
                    public void mouseClicked(MouseEvent e) {
                        onClickBlock(block);
                    }
                });

                gamePanel.add(block);
            }
        }

        // 初始化第一行的黑块（随机一列）
        generateBlackBlock(0);
        add(gamePanel, BorderLayout.CENTER);
    }

    /**
     * 初始化游戏定时器（控制方块滚动）
     */
    private void initTimer() {
        gameTimer = new Timer(speedLevel, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                moveBlocksDown(); // 方块向下滚动
                checkGameOver();   // 检查是否游戏结束
                increaseSpeed();  // 逐渐加快速度
            }
        });
        gameTimer.start(); // 启动定时器
    }

    /**
     * 生成黑块（指定行，随机列）
     * @param row 要生成黑块的行
     */
    private void generateBlackBlock(int row) {
        // 先清空该行所有方块颜色
        for (int j = 0; j < COLS; j++) {
            blocks[row][j].setBackground(Color.WHITE);
            blocks[row][j].setEnabled(true); // 启用方块
            blocks[row][j].setName("white"); // 标记为白块
        }
        // 随机选一列设为黑块
        int blackCol = random.nextInt(COLS);
        blocks[row][blackCol].setBackground(Color.BLACK);
        blocks[row][blackCol].setName("black"); // 标记为黑块
    }

    /**
     * 方块向下滚动（核心逻辑）
     */
    private void moveBlocksDown() {
        // 从最后一行向前遍历，把上一行的颜色复制到当前行
        for (int i = ROWS - 1; i > 0; i--) {
            for (int j = 0; j < COLS; j++) {
                blocks[i][j].setBackground(blocks[i - 1][j].getBackground());
                blocks[i][j].setName(blocks[i - 1][j].getName());
            }
        }
        // 第一行重新生成黑块
        generateBlackBlock(0);
    }

    /**
     * 点击方块的事件处理
     * @param block 被点击的方块
     */
    private void onClickBlock(JButton block) {
        if (gameTimer.isRunning()) {
            if ("black".equals(block.getName())) {
                // 点击黑块：得分，标记为已点击（变灰色）
                score++;
                scoreLabel.setText("分数：" + score);
                block.setBackground(Color.GRAY);
                block.setName("clicked");
                block.setEnabled(false);
            } else {
                // 点击白块：游戏结束
                gameOver();
            }
        }
    }

    /**
     * 检查游戏结束（最后一行的黑块未被点击则结束）
     */
    private void checkGameOver() {
        for (int j = 0; j < COLS; j++) {
            JButton lastBlock = blocks[ROWS - 1][j];
            // 最后一行有未被点击的黑块 → 游戏结束
            if ("black".equals(lastBlock.getName())) {
                gameOver();
                break;
            }
        }
    }

    /**
     * 逐渐加快游戏速度（【修改2：放慢递增节奏】）
     */
    private void increaseSpeed() {
        // 调整：每得10分才加快一次，且每次只减5毫秒，最低不低于150毫秒（避免太快）
        if (score % 10 == 0 && score != 0 && speedLevel > 150) {
            speedLevel -= 5; // 间隔减少5毫秒（速度变快）
            gameTimer.setDelay(speedLevel);
        }
    }

    /**
     * 游戏结束处理
     */
    private void gameOver() {
        gameTimer.stop(); // 停止定时器
        // 弹出提示框，询问是否重新开始
        int choice = JOptionPane.showConfirmDialog(
                this,
                "游戏结束！你的分数：" + score + "\n是否重新开始？",
                "游戏结束",
                JOptionPane.YES_NO_OPTION
        );
        if (choice == JOptionPane.YES_OPTION) {
            restartGame(); // 重新开始
        } else {
            System.exit(0); // 退出程序
        }
    }

    /**
     * 重新开始游戏（同步重置速度）
     */
    private void restartGame() {
        score = 0;
        speedLevel = 300; // 【修改3：重新开始时恢复慢初始速度】
        scoreLabel.setText("分数：0");
        // 重置所有方块
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                blocks[i][j].setBackground(Color.WHITE);
                blocks[i][j].setName("white");
                blocks[i][j].setEnabled(true);
            }
        }
        // 重新生成第一行黑块
        generateBlackBlock(0);
        // 重启定时器
        gameTimer.setDelay(speedLevel);
        gameTimer.start();
    }

    /**
     * 主方法：启动游戏
     */
    public static void main(String[] args) {
        // Swing组件必须在事件调度线程（EDT）中创建
        SwingUtilities.invokeLater(() -> {
            new DontStepWhiteBlock().setVisible(true);
        });
    }
}