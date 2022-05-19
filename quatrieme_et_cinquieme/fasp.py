from ast import Pass
import numpy as np

def FastAndEffectiveFAS(G):
  M = G.m
  n = M.shape[0]
  
  do = M.sum(axis=1, dtype=np.float)
  di = M.sum(axis=0, dtype=np.float)
 
  s1 = []
  s2 = []
 
  for _ in range(n):
    snk = np.nanargmin(do)
    if do[snk] == 0:
      s2.append(snk)
      v = snk
    else:
      src = np.nanargmin(di)
      if di[src] != 0:
        dd = do - di
        src = np.nanargmax(dd)
      s1.append(src)
      v = src
    
    do -= M[:,v]
    di -= M[v]
    do[v] = di[v] = np.nan
  
  s = s1 + s2[::-1]
  return s

def main():
    pass

if __name__ == "__main__":
    main()