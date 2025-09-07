// sniff_pcap.c
#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>   // struct ether_header
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/types.h>

#define SNAP_LEN 1518

void packet_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    const struct ether_header *eth = (struct ether_header*)bytes;
    printf("\n=== Ethernet ===\n");
    printf("Src MAC: %s\n", ether_ntoa((struct ether_addr*)eth->ether_shost));
    printf("Dst MAC: %s\n", ether_ntoa((struct ether_addr*)eth->ether_dhost));

    if (ntohs(eth->ether_type) != ETHERTYPE_IP) return;
    const struct ip *ip = (struct ip*)(bytes + sizeof(struct ether_header));
    char srcip[INET_ADDRSTRLEN], dstip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ip->ip_src, srcip, sizeof(srcip));
    inet_ntop(AF_INET, &ip->ip_dst, dstip, sizeof(dstip));
    printf("--- IPv4 ---\n");
    printf("Src IP: %s\nDst IP: %s\nProto: %u\n",
           srcip, dstip, ip->ip_p);

    if (ip->ip_p != IPPROTO_TCP) return;
    int ip_hdr_len = ip->ip_hl * 4;
    const struct tcphdr *tcp = (struct tcphdr*)(bytes + sizeof(struct ether_header) + ip_hdr_len);
    printf("--- TCP ---\n");
    printf("Src Port: %u\nDst Port: %u\n",
           ntohs(tcp->source), ntohs(tcp->dest));

    int tcp_hdr_len = tcp->doff * 4;
    const u_char *app_data = bytes  
        + sizeof(struct ether_header)
        + ip_hdr_len
        + tcp_hdr_len;
    int app_len = h->len 
        - (sizeof(struct ether_header) + ip_hdr_len + tcp_hdr_len);
    if (app_len > 0) {
        printf("--- Payload (%d bytes) ---\n", app_len);
        for (int i = 0; i < app_len; i++) {
            printf("%02x ", app_data[i]);
            if ((i+1)%16 == 0) printf("\n");
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <interface>\n", argv[0]);
        return 1;
    }
    char *dev = argv[1], errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live(dev, SNAP_LEN, 1, 1000, errbuf);
    if (!handle) {
        fprintf(stderr, "pcap_open_live: %s\n", errbuf);
        return 2;
    }
    // optional: set a BPF filter, e.g. only TCP: 
    struct bpf_program fp;  
    if (pcap_compile(handle, &fp, "tcp", 1, PCAP_NETMASK_UNKNOWN)==0)
        pcap_setfilter(handle, &fp);

    pcap_loop(handle, 0, packet_handler, NULL);
    pcap_close(handle);
    return 0;
}
