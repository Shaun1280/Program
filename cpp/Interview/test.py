from functools import lru_cache

class Solution:
    def countKReducibleNumbers(self, s: str, k: int) -> int:
        n = len(s)
        num_ones = [[] for _ in range(6)]
        for x in range(1, n):
            cnt = 0
            val = x
            while x != 1:
                cnt += 1
                x = x.bit_count()
            if cnt <= 5:
                num_ones[cnt].append(val)
        
        mod = 10**9 + 7
        self.ans = 0

        @lru_cache()
        def dp(step, isLimit, cnt, target_cnt):
            if step == n:
                if not isLimit and cnt == target_cnt:
                    return 1
                else:
                    return 0

            ret = 0
            if not isLimit:
                ret += dp(step + 1, False, cnt, target_cnt)
                ret += dp(step + 1, False, cnt + 1, target_cnt)
            else:
                for i in range(int(s[step]) + 1):
                    if i == int(s[step]):
                        if i == 1:
                            ret += dp(step + 1, True, cnt + 1, target_cnt)
                        else:
                            ret += dp(step + 1, True, cnt, target_cnt)
                    else:
                        ret += dp(step + 1, False, cnt, target_cnt)

            return ret % mod

        for i in range(k):
            for x in num_ones[i]:
                print(x)
                self.ans += dp(0, True, 0, x)
                # print(self.ans)
                self.ans %= mod
        
        return self.ans


s = Solution()
print(s.countKReducibleNumbers('1000', 2))


