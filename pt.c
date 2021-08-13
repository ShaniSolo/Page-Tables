#include "os.h"
//Q 1
void page_table_update(uint64_t pt, uint64_t vpn, uint64_t ppn)
{	
    uint64_t vpn_array[5];
    vpn = vpn >> 12;
    for(int i = 4 ;i >= 0; i--)
    {	
    	vpn_array[i] = 0x1ff & vpn;
    	vpn = vpn >> 9;
    }
    uint64_t* virtual_address = phys_to_virt(pt<<12);
	uint64_t phys_address;
    if(ppn == NO_MAPPING)
    {
    	for(int i=0; i<4; i++)
    	{
    		phys_address = (virtual_address[vpn_array[i]]);
    		if(phys_address == (phys_address >> 1 << 1))
    			return;
    		phys_address = phys_address >> 1 << 1;
    		virtual_address = phys_to_virt(phys_address);
    	}
    	(virtual_address[vpn_array[4]]) = (virtual_address[vpn_array[4]]) >> 1 << 1;
    }
    else
    {
      	for(int i=0; i<4; i++)
    	{
		 	phys_address = (virtual_address[vpn_array[i]]);
			if(phys_address == (phys_address >> 1 << 1))
    		{
		    	uint64_t new_ad = alloc_page_frame();
		    	virtual_address[vpn_array[i]] = (new_ad<<12) | 1;
		    	phys_address = new_ad<<12;
		    	virtual_address = phys_to_virt(phys_address);
		    }
		    else
		    {
		    	phys_address = phys_address >> 1 << 1;
    			virtual_address = phys_to_virt(phys_address);
		    }
     	}
     	virtual_address[vpn_array[4]] = (ppn<<12) | 1;
    }
}
//Q 2
uint64_t page_table_query(uint64_t pt, uint64_t vpn)
{   
    uint64_t vpn_array [5];
    vpn = vpn >> 12;
 	for(int i = 4 ;i >= 0; i--)
    {	
    	vpn_array[i] = 0x1ff & vpn;
    	vpn = vpn >> 9;
    }
    uint64_t* virtual_address = phys_to_virt(pt<<12);
	uint64_t phys_address;
	for(int i=0; i<4; i++)
	{
		phys_address = (virtual_address[vpn_array[i]]);
		if(phys_address == (phys_address >> 1 << 1))
		{
			return NO_MAPPING;
		}
		phys_address = phys_address >> 1 << 1;
		virtual_address = phys_to_virt(phys_address);
	}
	phys_address = (virtual_address[vpn_array[4]]);
	if(phys_address == (phys_address >> 1 << 1))
		return NO_MAPPING;
	uint64_t ppn =  virtual_address[vpn_array[4]] >> 12;	
	return ppn;
}


