# 题目：Chap05-2 线段树 City Horizon（poj 3277）

## 问题描述
Farmer John has taken his cows on a trip to the city! As the sun sets, the cows gaze at the city horizon and observe the beautiful silhouettes formed by the rectangular buildings.

The entire horizon is represented by a number line with N (1 ≤ N ≤ 40,000) buildings. Building i's silhouette has a base that spans locations Ai through Bi along the horizon (1 ≤ Ai < Bi ≤ 1,000,000,000) and has height Hi (1 ≤ Hi ≤ 1,000,000,000). Determine the area, in square units, of the aggregate silhouette formed by all N buildings.

## 输入格式
Line 1: A single integer: N 

Lines 2..N+1: Input line i+1 describes building i with three space-separated integers: Ai, Bi, and Hi
## 输出格式
Line 1: The total area, in square units, of the silhouettes formed by all N buildings
## 输入样例
	4
	2 5 1
	9 10 4
	6 8 2
	4 6 3
## 输出样例
	16

## Hint

	The first building overlaps with the fourth building for an area of 1 square unit, so the total area is just 3*1 + 1*4 + 2*2 + 2*3 - 1 = 16.

----