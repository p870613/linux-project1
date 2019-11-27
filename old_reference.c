#include<linux/kernel.h>
#include<linux/syscalls.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/proc_fs.h>
#include<linux/pid.h>
#include<linux/sched.h>
#include<linux/mm.h>
#include<linux/mm_types.h>
#include<linux/highmem.h>
#include<linux/string.h>

int phy_counter;
int vir_counter;

static unsigned long convert_to_phy_add(struct mm_struct *mm, unsigned long vir_add)
{
	unsigned long phy_add;
	pgd_t *pgd = NULL;
	pud_t *pud = NULL;
	pmd_t *pmd = NULL;
	pte_t *pte = NULL;
	p4d_t *p4d = NULL;
	struct page *pg = NULL;

	pgd = pgd_offset(mm, vir_add);

	if(pgd_none(*pgd) || pgd_bad(*pgd))
		return 0;

	p4d = p4d_offset(pgd, vir_add);

	if(p4d_none(*p4d) || p4d_bad(*p4d))
		return 0;

	pud = pud_offset(p4d, vir_add);

	if(pud_none(*pud) || pud_bad(*pud))
		return 0;

	pmd = pmd_offset(pud, vir_add);

	if(pmd_none(*pmd) || pmd_bad(*pmd))
		return 0;
	
	if (!(pte = pte_offset_map(pmd, vir_add)))
        return 0;

	if (!(pg = pte_page(*pte)))
		return 0;

	phy_add = page_to_phys(pg);
	pte_unmap(pte);

	phy_counter++;
	return phy_add;

}
/*
void vm_table(struct task_struct *task,char* result)
{
    struct vm_area_struct *cur = task->mm->mmap;
	unsigned long start;
	unsigned long end;
	//int count_null = 0, count_all = 0;
        while(cur != NULL)
        {	
			vir_counter++;
            start = cur->vm_start;
            end = cur->vm_end;
			printk("%lx %lx\n", start, convert_to_phy_add(task->mm, start));
			printk("%lx %lx\n", end, convert_to_phy_add(task->mm, end));
			cur = cur -> vm_next;
		}

}
*/

void vm_table_old(struct task_struct *task,char* result)
{
    struct vm_area_struct *cur = task->mm->mmap;
	
	int count_null = 0, count_all = 0;
	unsigned long start, end, phy;
	int offset;
        while(cur != NULL)
        {
			vir_counter++;
			start = cur->vm_start;
			end = cur->vm_end;
			int flag = 0;
			char tmp[27];
			int i = 0, looker = 0;		

			phy = convert_to_phy_add(task->mm,start);
		
			// put the information into the array tmp
			if( phy != 0 ){
				flag = 1;
				//snprintf(tmp, 27, "%lx%lx%d%lx", start, end, flag, phy);
				printk("%lx%lx%d%lx", start, end, flag, phy);
			}
			else{
				flag = 0;
				count_null++;
				//snprintf(tmp, 27, "%lx%lx%d%s", start, end, flag, "00000000");
				printk("%lx%lx%d%s", start, end, flag, "00000000");
			}

			count_all++;
		
			/* The layout of result:
			* -------------------------
			* |  8  |  8  |  1  |  8  |
			* -------------------------
			*   vm_s  vm_e  flag  phy
			*
			* lenth: 25 bytes
			*/
			
			// assign the data from tmp
			offset = (count_all - 1) * 26;
			for( looker = offset; looker < offset + 26; looker++, i++ ){
				if( tmp[i] == '\0' ){
					result[looker] = ' '; // when the physical address is less than 8 characters
				}
				else{
					result[looker] = tmp[i];
				}
			}

			result[(count_all * 26 - 1)] = '\n';

			cur = cur -> vm_next;
		
        }
	// put the final characters in the end of result
	result[(count_all * 26)] = 'h';
	result[(count_all * 26) + 1] = '\0';
}


asmlinkage long sys_linux_survey_TT(char* result)
{
    //struct pid *pid_struct;
    struct task_struct *task = get_current();
	printk("YahaRo\n");
	printk("Table v6--------\n");

        //printk("%d", task->pid);
        //pid_struct = find_get_pid(task->pid);

	phy_counter = 0;
	vir_counter = 0;
    vm_table_old(task,result);
	printk("Percentage %d/%d\n",phy_counter,vir_counter);
	printk("ByeBye~\n");

        return 0;
}
