h = initializare minHeap
pt fiecare nod initializare
    h->pos[i] = i;
    adaug in h cu por infinit
h[0] = 0
cat timp mai exista noduri in minHeap 
    u = removeMin(h)
    pt fiecare vecin al lui u:
        daca v este in h si dist[v] > dist[u] + muchieUV
            d[v] = d[u] + Wuv
            h[v] = d[v]
            siftUp(h,v,d[v])

daistra

h = initializare minHeap
pt fiecare nod initializare
    h->pos[i] = i;
    adaug in h cu por infinit
h[0] = 0
cat timp mai exista noduri in minHeap 
    u = removeMin(h)
    pt fiecare vecin al lui u:
        daca v este in h si dist[v] >   muchieUV
            d[v] =  Wuv
            h[v] = d[v]
            siftUp(h,v,d[v])

p[n]
h = initializare minHeap
pt fiecare nod initializare
    h->pos[i] = i;
    adaug in h cu por infinit
h[0] = 0
cat timp mai exista noduri in minHeap 
    u = removeMin(h)
    pt fiecare vecin al lui u:
        daca v este in h si dist[v] > dist[u] + muchieUV
            d[v] = d[u] + Wuv
            p[v] = u
            h[v] = d[v]
            siftUp(h,v,d[v])

