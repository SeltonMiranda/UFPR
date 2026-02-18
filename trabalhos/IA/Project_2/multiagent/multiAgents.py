# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent
from pacman import GameState

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState: GameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState: GameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        foodList = newFood.asList()

        if len(foodList) == 0:
            return 100000 # Ganhou

        heuristic = successorGameState.getScore()
        ghostsPositions = [ghost.getPosition() for ghost in newGhostStates]


        ghostDistances = [manhattanDistance(ghostP, newPos) for ghostP in ghostsPositions]
        foodDistances  = [manhattanDistance(foodP, newPos) for foodP in foodList]

        closerGhost = min(ghostDistances) if ghostDistances else 1
        closerFood  = min(foodDistances)  if foodDistances  else 1
        leastScared = min(newScaredTimes) if newScaredTimes else 0

        """
        Basicamente, quanto mais distante e mais comida sobrar, maior a penalidade.
        Nos testes, quanto menor a distância da comida, menos penalidade o pacman
        recebia ao invés de comê-la, portanto o pacman ficava travado. Para resolver isso
        mostCloseFood foi multiplaco por 0.5
        """
        remainingFood = len(foodList)
        foodFactor  = -closerFood * 0.5 - 2 * remainingFood

        if closerGhost <= 1 and leastScared == 0:
            """
            O fantasma está muito próximo, então morrer tem uma penalidade muito alta
            """
            return -999999  
        else:
            """
            Queremos o fantasma o mais longe possível
            Quanto mais próximo do pacman, a fração se aproxima de -20
            Quanto mais longe, a fração se aproxima de 0
            """
            ghostFactor = - 20 / closerGhost

        # Se os fantasmas estiverem assutados, o pacman pode se aproximar/comê-los
        if leastScared > 0:
            ghostFactor = -ghostFactor

        heuristic += foodFactor + ghostFactor
        return heuristic

def scoreEvaluationFunction(currentGameState: GameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"

        actions = gameState.getLegalActions(0)
        bestScore = float('-inf')
        bestAction = None

        for action in actions:
            newState = gameState.generateSuccessor(0, action)
            score = self.minimax(self.depth, 1, newState)
            if score > bestScore:
                bestScore = score
                bestAction = action
        
        return bestAction
    
    def minimax(self, depth, agent, gameState: GameState):
        """
        Igual ao slides 
        """
        if depth == 0 or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)
        
        newAgent = (agent + 1) % gameState.getNumAgents()
        newDepth = depth - 1 if newAgent == 0 else depth 
        actions = gameState.getLegalActions(agent)

        if agent == 0:

            v = float('-inf')
            for action in actions:
                newState = gameState.generateSuccessor(agent, action)
                v = max(v, self.minimax(newDepth, newAgent, newState))
            return v

        else:

            v = float('inf')
            for action in actions:
                newState = gameState.generateSuccessor(agent, action)
                v = min(v, self.minimax(newDepth, newAgent, newState))
            return v


class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"

        actions = gameState.getLegalActions(0)
        bestScore = float('-inf')
        alpha = float('-inf')
        beta = float('inf')
        bestAction = None

        for action in actions:
            newState = gameState.generateSuccessor(0, action)
            score = self.minimaxAB(self.depth, 1, alpha, beta, newState)

            if score > bestScore:
                bestScore = score
                bestAction = action

            alpha = max(alpha, bestScore)
 
        return bestAction
    
    def minimaxAB(self, depth, agent, alpha, beta, gameState: GameState):
        """
        Igual ao slides 
        """
        if depth == 0 or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)

        newAgent = (agent + 1) % gameState.getNumAgents()
        newDepth = depth - 1 if newAgent == 0 else depth 
        actions = gameState.getLegalActions(agent)
        
        if agent == 0:

            v = float('-inf') 
            for action in actions:
                newState = gameState.generateSuccessor(agent, action)
                v = max(v, self.minimaxAB(newDepth, newAgent, alpha, beta, newState))

                if v > beta: return v
                alpha = max(alpha, v)

            return v

        else:

            v = float('inf') 
            for action in actions:
                newState = gameState.generateSuccessor(agent, action)
                v = min(v, self.minimaxAB(newDepth, newAgent, alpha, beta, newState))

                if v < alpha: return v
                beta = min(beta, v)

            return v

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        actions = gameState.getLegalActions(0)
        bestScore = float('-inf')
        bestAction = None

        for action in actions:
            newState = gameState.generateSuccessor(0, action)
            score = self.expectimax(self.depth, 1, newState)

            if score > bestScore:
                bestScore = score
                bestAction = action
 
        return bestAction

    def expectimax(self, depth, agent, gameState: GameState):
        """
        Igual ao slides 
        """
        if depth == 0 or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)
        
        newAgent = (agent + 1) % gameState.getNumAgents()
        newDepth = depth - 1 if newAgent == 0 else depth 
        actions = gameState.getLegalActions(agent)

        if agent == 0:

            v = float('-inf')
            for action in actions:
                newState = gameState.generateSuccessor(agent, action)
                v = max(v, self.expectimax(newDepth, newAgent, newState))
            return v

        else:

            prob = 1.0 / len(actions)
            v = 0
            for action in actions:
                newState = gameState.generateSuccessor(agent, action)
                v += prob * self.expectimax(newDepth, newAgent, newState)
            return v

def betterEvaluationFunction(currentGameState: GameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION:
    Basicamente, a mesma ideia da questão 1, a diferença é que agora
    há um incentivo para pegar as cápsulas e a heuristica melhora quanto mais longe dos
    fantasmas, pois agora temos mais fantasmas, ao contrário da questão 1
    """
    "*** YOUR CODE HERE ***"
    pacmanPos = currentGameState.getPacmanPosition()
    food = currentGameState.getFood()
    foodlist = food.asList()
    capsules = currentGameState.getCapsules()
    ghosts = currentGameState.getGhostStates()

    heuristic = currentGameState.getScore()

    if foodlist:
        minDistFood = min([manhattanDistance(pacmanPos, food) for food in foodlist])
        heuristic += 10 / minDistFood
    
    for ghost in ghosts:
        ghostPos = ghost.getPosition()
        dist = manhattanDistance(pacmanPos, ghostPos)

        if ghost.scaredTimer > 0: heuristic += 20 / (dist + 0.1)
        else:
            if dist <= 1: heuristic -= 500
            else:         heuristic -= 5 / (dist + 0.1)
    
    for capsule in capsules:
        heuristic += 5 / (manhattanDistance(pacmanPos, capsule) + 0.1)
    
    remainingFood = len(foodlist)
    remainingCapsules = len(capsules)

    heuristic -= (4 * remainingFood + 20 * remainingCapsules)
    return heuristic

# Abbreviation
better = betterEvaluationFunction
