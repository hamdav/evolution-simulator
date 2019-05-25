// Depth first search for determining if a graph is coherent

using System;
using System.Linq;

public class DFS{
    public static void Main(){
        //int[][] architecture = new int[][] {new int[] {1,2},new int[] {0},new int[] {0}};
        int[][] architecture = new int[][] {new int[] {1,2},new int[] {0},new int[] {0,4},new int[] {4}, new int[] {3,2}};

        if (IsConnected(architecture)){
            Console.WriteLine("Ye mate");
        } 
        else{
            Console.WriteLine("Na mate");
        }

    }
    public static bool IsConnected(int[][] graph){
        int n = graph.Length;

        // Alla element i seen borde vara false utom första. 
        bool[] seen = new bool[n];
        seen[0] = true;
        // Alla element i visited borde vara false
        bool[] visited = new bool[n];

        int currentNode = 0;
        while (true){
            visited[currentNode] = true;
            foreach (int ID in graph[currentNode]){
                seen[ID] = true;
            }
            bool found = false;
            for (int nextNode = 1; nextNode < n; nextNode++){
                if (seen[nextNode] && !visited[nextNode]){
                    currentNode = nextNode;
                    found = true;
                    break;
                }
            }
            if (seen.All(x=>x)){
                return true;
            }
            if (!found){
                return false;
            }
        }
    }
}