# Stefan Dierauf sdierauf@cs 1232328
# University of Washington, Programming Languages, Homework 6, hw6runner.rb

# This is the only file you turn in, so do not modify the other files as
# part of your solution.

class MyPiece < Piece
  # The constant All_My_Pieces should be declared here
  All_My_Pieces = [
    [
      [[-2, 0], [-1, 0], [0, 0], [1, 0], [2, 0]], #5 long
      [[0, -2], [0, -1], [0, 0], [0, 1], [0, 2]]
    ],
    rotations([[0, 0], [0, 1], [1, 0]]), # 3 L
    rotations([[-1, -1], [-1, 0], [0, -1], [0, 0], [1, 0]]) #weird one
  ].concat(All_Pieces)
  # your enhancements here

  def self.next_piece (board)
    MyPiece.new(All_My_Pieces.sample, board)
  end

  def self.cheat_piece (board)
    MyPiece.new([[[0, 0]]], board)
  end

end

class MyBoard < Board
  # your enhancements here
  
  def initialize(game)
    super(game)
    @current_block = MyPiece.next_piece(self)
    @cheating = false
  end

  def next_piece
    @current_block = MyPiece.next_piece(self)
    if (@cheating) 
      @current_block = MyPiece.cheat_piece(self)
      @cheating = false
    end
    @current_pos = nil
  end

  def attempt_cheat
    if (@score > 100)
      if (!@cheating)
        @cheating = true
        @score = @score - 100
      end
    end
  end

  def store_current
    locations = @current_block.current_rotation
    displacement = @current_block.position
    num_blocks = @current_block.current_rotation.length
    (0..(num_blocks - 1)).each{|index|
      current = locations[index];
      @grid[current[1]+displacement[1]][current[0]+displacement[0]] = 
      @current_pos[index]
    }
    remove_filled
    @delay = [@delay - 2, 80].max
  end

end

class MyTetris < Tetris
  # your enhancements here.

  def set_board
    @canvas = TetrisCanvas.new
    @board = MyBoard.new(self)
    @canvas.place(@board.block_size * @board.num_rows + 3,
                  @board.block_size * @board.num_columns + 6, 24, 80)
    @board.draw
  end

  def key_bindings
    super
    @root.bind('c', lambda {self.trigger_cheat})
    @root.bind('u', lambda {@board.rotate_clockwise
                            @board.rotate_clockwise})
  end

  def trigger_cheat
    @board.attempt_cheat
  end
end


