/* sample code for Part 2 */      
#include <stdio.h>
#include <fcntl.h>

#include <sys/types.h>
#include <unistd.h>

typedef unsigned int u32;
typedef unsigned char  u8;
typedef unsigned short u16;

struct partition {
    u8 drive;             // drive number FD=0, HD=0x80, etc.

    u8  head;             // starting head 
    u8  sector;           // starting sector
    u8  cylinder;         // starting cylinder

    u8  sys_type;         // partition type: NTFS, LINUX, etc.

    u8  end_head;         // end head 
    u8  end_sector;       // end sector
    u8  end_cylinder;     // end cylinder

    u32 start_sector;     // starting sector counting from 0 
    u32 nr_sectors;       // number of of sectors in partition
};

char *dev = "vdisk";
int fd;
    
// read a disk sector into char buf[512]
int read_sector(int fd, int sector, char *buf)
{
    lseek(fd, sector*512, SEEK_SET);  // lssek to byte sector*512
    read(fd, buf, 512);               // read 512 bytes into buf[ ]
}

int main()
{
    struct partition *p;
    char buf[512];

    fd = open(dev, O_RDONLY);   // open dev for READ
    read_sector(fd, 0, buf);    // read in MBR at sector 0    

    p = (struct partition *)(&buf[0x1be]); // p->P1
    
    // *************** CHECKLIST 1 ******************
    // print P1's start_sector, nr_sectors, sys_type;
    printf("P1 Partition\n");
    printf("P1's start_sector: %d, P1's nr_sectors: %d, P1's sys_type: %x\n", p->start_sector, p->nr_sectors, p->sys_type);
    printf("\n");
    
    // Write code to print all 4 partitions;
    printf("All 4 Partitions\n");
    for (int i=1; i<5; i++) {
        printf("P%d's start_sector: %d, P%d's nr_sectors: %d, P%d's sys_type: %x\n", i, p->start_sector, i, p->nr_sectors, i, p->sys_type);
        p++;
    }

    //***************** CHECKLIST 2 ******************
    // ASSUME P4 is EXTEND type:
    int extStart = p->start_sector;
    // print extStart to see it;

    // p = extStart;
    // while (p->sys_type != NULL) {
    //     read_sector(fd, p, buf);
    //     p++;
    // }
        

        // partition table of localMBR in buf[ ] has 2 entries: 
        // print entry 1's start_sector, nr_sector;
        // compute and print P5's begin, end, nr_sectors

            //   if (entry 2's start_sector != 0){
            //      compute and print next localMBR sector;
            //      continue loop;
            //   }
}