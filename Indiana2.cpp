#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <set>
#include <stack>
#include <limits>

using namespace std;

// Direction implementation

class Direction
{
private:
    string name_;
    int dx_;
    int dy_;
    const Direction& opposite_;
    
public: 
    static const Direction TOP;
    static const Direction LEFT;
    static const Direction RIGHT;
    static const Direction BOTTOM;

    int dx() const { return dx_; }
    int dy() const { return dy_; }
    const string& name() const { return name_; }
    const Direction& opposite() const { return opposite_; }
    
    static const Direction* fromName(const string& name)
    {
        if (name == "TOP") return &TOP;        
        else if (name == "LEFT") return &LEFT;
        else if (name == "RIGHT") return &RIGHT;
        else if (name == "BOTTOM") return &BOTTOM;
        return nullptr;
    }
    
protected:
    Direction(const string& name, const int dx, const int dy, const Direction& opposite) 
        : name_(name), dx_(dx), dy_(dy), opposite_(opposite) {}
    Direction(const Direction&);
    Direction operator=(const Direction&);
};

const Direction Direction::TOP("TOP", 0, -1, Direction::BOTTOM);
const Direction Direction::LEFT("LEFT", -1, 0, Direction::RIGHT);
const Direction Direction::RIGHT("RIGHT", 1, 0, Direction::LEFT);
const Direction Direction::BOTTOM("BOTTOM", 0, 1, Direction::TOP);

// Point implementation

class Point
{
private:    
    int x_;
    int y_;
    
public:
    Point() : x_(), y_() {}
    Point(const int x, const int y) : x_(x), y_(y) {}
    int x() const { return x_; }
    int y() const { return y_; }
    Point operator+(const Direction& dir) const
    {
        return Point(x_ + dir.dx(), y_ + dir.dy());
    }
    bool operator==(const Point& other) const
    {
        return x_ == other.x_ && y_ == other.y_;
    }
    bool operator<(const Point& other) const
    {
        int d = x_ - other.x_;
        return d == 0 ? y_ - other.y_ : d;
    }
    int distance(const Point& other) const
    {
        return abs(other.x_ - x_) + abs(other.y_ - y_);
    }
    void set(const int x, const int y) { x_ = x; y_ = y; }
};

ostream& operator<<(ostream& out, const Point& p)
{
    out << p.x() << " " << p.y();
    return out;
}

// Puzzle Piece implementation

class PuzzlePiece
{
private:
    map<const Direction*, const Direction*> flows_;
    int index_;
    int minIndex_;
    int maxIndex_;
    typedef map<const Direction*, const Direction*>::const_iterator FlowConstIterator;
    
public:
    PuzzlePiece(map<const Direction*, const Direction*> flows, const int index, const int minIndex, const int maxIndex)
        : flows_(flows), index_(index), minIndex_(minIndex), maxIndex_(maxIndex) {}
    PuzzlePiece(const Direction* in, const Direction* out, const int index, const int minIndex, const int maxIndex) 
        : flows_({{in, out}}), index_(index), minIndex_(minIndex), maxIndex_(maxIndex) {}
    
    bool evaluate(const Point& inputPos, const Direction* inputDir, Point& outputPos, const Direction*& outputDir) const
    {
        if (inputDir == nullptr)
        {
            return false;
        }
        FlowConstIterator it = flows_.find(inputDir);
        if (it != flows_.cend())
        {
            outputDir = &(it->second->opposite());
            outputPos = inputPos + *it->second;
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool canEnter(const Direction* dir) const
    {
        return flows_.find(dir) != flows_.cend();
    }
    
    int rotate(const Direction* dir) const
    {
        int ni = index_ + dir->dx();
        if (ni < minIndex_ ) ni = maxIndex_;
        if (ni > maxIndex_ ) ni = minIndex_;
        return ni;
    }
    
    int index() const { return index_; }
    int minIndex() const { return minIndex_; }
    int maxIndex() const { return maxIndex_; }
};

class PuzzlePieceFactory
{
private:
    static const vector<PuzzlePiece> PIECES_SET;
    
    PuzzlePieceFactory();
    PuzzlePieceFactory(const PuzzlePieceFactory&);
    PuzzlePieceFactory& operator=(const PuzzlePieceFactory&);
    
public:
    static const PuzzlePiece* pieceAt(const int index)
    {
        return &PIECES_SET.at(index);
    }
};

const vector<PuzzlePiece> PuzzlePieceFactory::PIECES_SET = {
    PuzzlePiece({}, 0, 0, 0), // Type 0
    PuzzlePiece(     // Type 1
    {
        {&Direction::TOP, &Direction::BOTTOM}, 
        {&Direction::LEFT, &Direction::BOTTOM}, 
        {&Direction::RIGHT, &Direction::BOTTOM}         
    },  1, 1, 1), 
    PuzzlePiece(    // Type 2
    {
        {&Direction::LEFT, &Direction::RIGHT}, 
        {&Direction::RIGHT, &Direction::LEFT}
    },  2, 2, 3),
    PuzzlePiece(    // Type 3
        &Direction::TOP, &Direction::BOTTOM,
        3, 2, 3
    ),  
    PuzzlePiece(    // Type 4
    {
        {&Direction::TOP, &Direction::LEFT}, 
        {&Direction::RIGHT, &Direction::BOTTOM}
    },  4, 4, 5), 
    PuzzlePiece(    // Type 5
    {
        {&Direction::TOP, &Direction::RIGHT}, 
        {&Direction::LEFT, &Direction::BOTTOM}
    },  5, 4, 5), 
    PuzzlePiece(    // Type 6
    {
        {&Direction::LEFT, &Direction::RIGHT}, 
        {&Direction::RIGHT, &Direction::LEFT}
    },  6, 6, 9), 
    PuzzlePiece(    // Type 7
    {
        {&Direction::TOP, &Direction::BOTTOM}, 
        {&Direction::RIGHT, &Direction::BOTTOM}
    },  7, 6, 9),
    PuzzlePiece(    // Type 8
    {
        {&Direction::LEFT, &Direction::BOTTOM}, 
        {&Direction::RIGHT, &Direction::BOTTOM}
    },  8, 6, 9),
    PuzzlePiece(    // Type 9
    {
        {&Direction::LEFT, &Direction::BOTTOM}, 
        {&Direction::TOP, &Direction::BOTTOM}
    },  9, 6, 9),
    PuzzlePiece(&Direction::TOP, &Direction::LEFT, 10, 10, 13), // Type 10
    PuzzlePiece(&Direction::TOP, &Direction::RIGHT, 11, 10, 13), // Type 11
    PuzzlePiece(&Direction::RIGHT, &Direction::BOTTOM, 12, 10, 13), // Type 12
    PuzzlePiece(&Direction::LEFT, &Direction::BOTTOM, 13, 10, 13) // Type 13
};

// Position implementation
class Position
{
private:
    Point pos_;
    const Direction* dir_;
    
public:    
    Position() : Position(Point(), nullptr) {}
    Position(const Point& pos, const Direction* dir) : pos_(pos), dir_(dir) {}
    const Point& pos() const { return pos_; }
    const Direction* dir() const { return dir_; }
    void setPos(const Point& pos) { pos_ = pos; }
    void setDir(const Direction* dir) { dir_ = dir; }    
};


// Maze implementation
class MazePiece
{
private:
    const PuzzlePiece* piece_;
    bool locked_;
    
    const PuzzlePiece* state_;
    
public:
    MazePiece(const PuzzlePiece* piece, const bool locked)
        : piece_(piece), locked_(locked), state_(nullptr)
    {
    }    
    
    void assign(const PuzzlePiece* piece, const bool locked)
    {
        piece_ = piece;
        locked_ = locked;
    }
    
    const PuzzlePiece* piece() const { return piece_; }
    bool locked() const { return locked_; }
    void setPiece(const PuzzlePiece* piece) { piece_ = piece; }
    bool canEnter(const Position& pos) const { piece_->canEnter(pos.dir()); }
    bool move(const Position& in, Position& out)
    {
        Point outputPos;
        const Direction* outputDir;
        if (piece_->evaluate(in.pos(), in.dir(), outputPos, outputDir))
        {
            out.setPos(outputPos);
            out.setDir(outputDir);
            return true;
        }
        return false;
    }
    void rotate(const Direction* dir, const int times)
    {
        for (int c = times; c > 0; --c)
        {
            piece_ = PuzzlePieceFactory::pieceAt(piece_->rotate(dir));
        }
    }
    void save() { state_ = piece_; }
    void restore() { piece_ = state_; }
    bool changed() const { return state_ != piece_; }
};

class Maze
{
private:
    vector<MazePiece> pieces_;
    Point exit_;
    int width_;
    int height_;
    
public:
    Maze(const int width, const int height) : 
        pieces_(width * height, MazePiece(PuzzlePieceFactory::pieceAt(0), false)), 
        exit_(), width_(width), height_(height) 
    {
    }
       
    MazePiece& operator()(const Point& p)
    {
        return pieces_[p.x() + p.y() * width_];
    }
    
    void setExit(const Point& p) { exit_.set(p.x(), p.y()); }
    const Point& exit() const { return exit_; }
    bool checkBounds(const Point& p)
    {
        return p.x() >= 0 && p.x() < width_ && p.y() >= 0 && p.y() < height_;
    }
};

class Rotation
{
private:
    Point pos_;
    const Direction* dir_;

public:
    Rotation() : pos_(), dir_(nullptr) {}
    Rotation(const Point& pos, const Direction* dir)
        : pos_(pos), dir_(dir) {}                    

    const Point& pos() const { return pos_; }
    const Direction* dir() const { return dir_; }
    void setPos(const Point& p) { pos_ = p; }
    void setDir(const Direction* dir) { dir_ = dir; }
};

ostream& operator<<(ostream& out, const Rotation& r)
{
    out << r.pos() << " " << r.dir()->name();
    return out;
}

class Change
{
private:
    const PuzzlePiece* piece_;
    const Direction* dir_;
    int payload_;
    
public:
    Change(const PuzzlePiece* piece, const Direction* dir, const int payload)
        : piece_(piece), dir_(dir), payload_(payload) {}
    
    int payload() const { return payload_; }
    const PuzzlePiece* piece() const { return piece_; }
    const Direction* dir() const { return dir_; }
};

class PathFinder
{
private:
    Maze& maze_;
    
public:
    PathFinder(Maze& maze) : maze_(maze)
    {
    }
    
    bool solve(const Position& indy, const vector<Position>& rocks, stack<Rotation>& rotations)
    {
        bool res = findWayToExit(indy, 1, rotations);
        if (rocks.empty() || (!rotations.empty() && rotations.top().pos() == nextMove(indy).pos()))
        {
            return res;        
        }
        else
        {
            stack<Rotation>().swap(rotations);
            return blockRocks(indy, rocks, rotations);
        }
    }
    
private:    
    Position nextMove(const Position& in)
    {
        Position out;
        maze_(in.pos()).move(in, out);
        return out;
    }
    
    bool blockRocks(const Position& indy, const vector<Position>& rocks, stack<Rotation>& rotations)
    {
        int minLength = numeric_limits<int>::max();
        Point blockPos;
        for (vector<Position>::const_iterator it = rocks.cbegin();
            it != rocks.end();
            ++it)
        {
            const Position& rock = *it;
            
            Position in = rock;
            int len = 0;
            while (1)
            {
                MazePiece& mpIn = maze_(in.pos());
                Position out;
                if (!mpIn.move(in, out) || !maze_.checkBounds(out.pos()))
                {
                    break;
                }
                if (out.pos() == indy.pos())
                {
                    break;
                }
                ++len;                
                MazePiece& mpOut = maze_(out.pos());
                if (!mpOut.locked() && mpOut.canEnter(out))
                {
                    if (len < minLength)
                    {
                        minLength = len;
                        blockPos = out.pos();
                    }
                    break;
                }
                in = out;
            }
        }
        if (minLength != numeric_limits<int>::max())
        {
            rotations.push(Rotation(blockPos, &Direction::LEFT));
        }
        return false;
    }

    bool findWayToExit(const Position& in, int remainingChanges, stack<Rotation>& rotations)
    {
        MazePiece& mpIn = maze_(in.pos());
        if (in.pos() == maze_.exit())
        {
            return true;
        }
        
        Position out;
        if (!mpIn.move(in, out) || !maze_.checkBounds(out.pos()))
        {
            return false;
        }
        
        const vector<Change>& possibleChanges = getPossibleChanges(out, remainingChanges);
        MazePiece& mpOut = maze_(out.pos());
        bool found = false;
        for (vector<Change>::const_iterator it = possibleChanges.cbegin();
            it != possibleChanges.cend() && !found;
            ++it)
        {
            const Change& change = *it;
            mpOut.save();
            mpOut.rotate(change.dir(), change.payload());
            if (findWayToExit(out, 1 + remainingChanges - change.payload(), rotations))
            {
                found = true;
                if (change.dir() != nullptr)
                {
                    for (int i = 0; i < change.payload(); ++i)
                    {
                        rotations.push(Rotation(out.pos(), change.dir()));
                    }
                }
            }
            mpOut.restore();
        }
        return found;
    }
        
    vector<Change> getPossibleChanges(const Position& in, const int remainingChanges)
    {
        vector<Change> changes;
        
        MazePiece& mp = maze_(in.pos());
        if (mp.canEnter(in))
        {
            changes.push_back(Change(mp.piece(), nullptr, 0));
        }
        if (!mp.locked())
        {
            static vector<const Direction*> RotationDirs = {&Direction::LEFT, &Direction::RIGHT};
            for (vector<const Direction*>::const_iterator it = RotationDirs.cbegin();
                it != RotationDirs.cend();
                ++it)
            {
                const Direction* rotationDir = *it;
                mp.save();
                for (int payload = 1; payload <= remainingChanges; ++payload)
                {
                    mp.rotate(rotationDir, 1);
                    if (!mp.changed())
                    {
                        break;
                    }
                    if (mp.canEnter(in))
                    {
                        changes.push_back(Change(mp.piece(), rotationDir, payload));
                    }
                } 
                mp.restore();
            }
        }
        return changes;
    }
};



/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int W; // number of columns.
    int H; // number of rows.
    cin >> W >> H; cin.ignore();
    Maze maze(W, H);
    for (int y = 0; y < H; y++) {
        string LINE; // each line represents a line in the grid and contains W integers T. The absolute value of T specifies the type of the room. If T is negative, the room cannot be rotated.
        getline(cin, LINE);
        istringstream iss(LINE);
        for (int x = 0, p; iss >> p; ++x)
        {            
            maze(Point(x, y)).assign(PuzzlePieceFactory::pieceAt(abs(p)), p < 0);
        }
        
    }
    int EX; // the coordinate along the X axis of the exit.
    cin >> EX; cin.ignore();
    maze.setExit(Point(EX, H - 1));

    // game loop
    PathFinder pathFinder(maze);
    while (1) {
        int XI;
        int YI;
        string POSI;
        cin >> XI >> YI >> POSI; cin.ignore();
        int R; // the number of rocks currently in the grid.
        cin >> R; cin.ignore();        
        vector<Position> rocks;
        for (int i = 0; i < R; i++) {
            int XR;
            int YR;
            string POSR;
            cin >> XR >> YR >> POSR; cin.ignore();
            rocks.push_back(Position(Point(XR, YR), Direction::fromName(POSR)));
        }
        Position indy(Point(XI, YI), Direction::fromName(POSI));
        stack<Rotation> rotations;
        pathFinder.solve(indy, rocks, rotations);
        if (rotations.empty())
        {
            cout << "WAIT" << endl;
        }
        else
        {
            const Rotation& r = rotations.top();
            cout << r << endl;
            maze(r.pos()).rotate(r.dir(), 1);
            rotations.pop();
        }
        
    }
}