# DragonBall
A  c++ console application to reconstruct a clapping game in my middle school.  
The names of moves are modified to facilitate understanding.

Details of the game  
**Basics and terminology**
1. Two players exert **moves** at the same time in every round.
2. **Moves** include **attack** (small, middle and big), **save energy**, and **defense**(small, middle and big).  
3. There is a key parameter called **energy** which is the basis for certain moves. 

**Release of energy**    
4. During an **attack**, certain amount of **energy** is released. 1 energy for small attack, 2 energy for middle attack and 5 energy for large attack.  
5. No energy is released during a small defense or middle defense.   
6. During a big defense, 3 energy is released.   
7. When energy is overused, i.e. negative energy appears, the game is over.   

**Acquisition of energy & How to win**  
8. After **save energy**, 1 energy is added.   
9. When a player attacks, there are three ways that the other can survive:  
  a. Make an attack with **higher level** (e.g. middle attack--small attack).   
  b. Make the **same attack** (e.g. small attack--small attack).   
  c. Apply **corresponding defense** (e.g. small attack--small defense).   
  Otherwise the player who attack wins and the attacked player loses.  
10. When the case in 9 a. occurs, the player exerting an attack with higher level wins.  
11. When the case in 9 b. occurs, the player who defense absorbs energy released by player who attacks (**unilateral absorption**).  
12. When the case in 9 c. occurs, both player absorb energy released by the other (**Mutual absorption**).    

**Examples**  
Example 1   
  Round 1  
    Player A: Save energy.  Player B: Save energy.   
    (Both players have 1 energy after round 1)   
  Round 2   
    Plyaer A: Small attack. Player B: Save energy.  
    Player A wins because player B does not make the same attack(as in 9 a.) or corresponding defense (as in 9.b).   
    
Example 2  
  Round 1  
    Player A: Save energy.  Player B: Save energy.   
  Round 2   
    Player A: Small defense.  Player B: Small attack.   
    (Unilateral absorption. A has 2 energy and B has 0 energy.)  
  Round 3  
    Player A: Save energy.  Player B: Save energy.   
  Round 3  
    Player A: Middle attack. Player B: Small attack.  
    Player A wins because A makes an attack with higher level.   

Example 3   
  Round 1   
    Player A: Save energy.  Player B: Save energy.   
  Round 2   
    Player A: Small attack. Player B: Small attack.  
    (Mutual absorption. Both player have 1 energy after round 2.)  
  Round 3   
    Player A: Save energy.  Player B: Save energy.  
  Round 4  
    Player A: Small attack. Player B: Middle defense.  
    Player A wins because the defense by player B does **NOT** correspond with A's attack.   

Example 4  
	Round 1-5  
		Player A: Save energy.  Player B: Save energy.   
	Round 6  
		Player A: Big attack. Player B: Big defense.  
		(Player A releases 5 energy to attack. Player B releases 3 energy to make big defense.   
		Unilateral absorption occurs so that A has 0 energy while B has 7 energy after round 6.)  
	Round 7  
		Player A: Middle defense. Player B: Big attack.  
		Player B wins.   
    
