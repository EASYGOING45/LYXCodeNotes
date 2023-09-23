"""
老王是一名木匠，他接到一项任务，要用非常珍贵的木材制作画框。这些木材的形态是比较均匀但长短不齐的木条，他的任务就是把这些木条首尾相连拼接成正方形的相框，为了避免珍贵材料浪费，给定一组木材后，不允许切割，并且不允许剩余，请帮助老王确认给定的材料能否拼接相框
输入 [21,21,21,21,42,42,84,84,84,84] 应该输出true
"""

class Solution:
    def CheckSquare(self, planks: List[int]) -> bool:
        total_sum = sum(planks)
        if total_sum % 4 != 0:
            return False
        side_length = total_sum // 4
        planks.sort(reverse=True)
        sides = [0] * 4
        for plank in planks:
            for i in range(4):
                if sides[i] + plank <= side_length:
                    sides[i] += plank
                    break
            else:
                return False
        return all(side == side_length for side in sides)
