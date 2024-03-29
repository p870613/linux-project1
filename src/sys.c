
static unsigned long convert_to_phy_add(struct mm_struct *mm, unsigned long long vir_add)
{
	unsigned long phy_add;
	pgd_t *pgd = NULL;
	pud_t *pud = NULL;
	pmd_t *pmd = NULL;
	pte_t *pte = NULL;
	p4d_t *p4d = NULL;
	struct page *pg = NULL;

	/*Page Global Directory*/
	pgd = pgd_offset(mm, vir_add);
	if(pgd_none(*pgd) || pgd_bad(*pgd))
		return 0;
	/*如果page大於4 才會使用*/
	p4d = p4d_offset(pgd, vir_add);
	if(p4d_none(*p4d) || p4d_bad(*p4d))
		return 0;

	/*Page Upper Directory*/
	pud = pud_offset(p4d, vir_add);
	if(pud_none(*pud) || pud_bad(*pud))
		return 0;
	/*Page Middle Directory*/
	pmd = pmd_offset(pud, vir_add);
	if(pmd_none(*pmd) || pmd_bad(*pmd))
		return 0;

	/*Page Table*/
	if (!(pte = pte_offset_map(pmd, vir_add)))
        return 0;

    // pte_page -> page的physical address
	if (!(pg = pte_page(*pte)))
		return 0;

	phy_add = page_to_phys(pg);
	pte_unmap(pte);
	return phy_add;

}

// save and printk the projects problems
void vm_table(struct task_struct *task, char* result)
{
	//counter number of pages with no physical address / number of pages / number of VMA
	int no_phy_count = 0, tatol_count = 0, vma_count = 0;
    
	unsigned long vpage;
	struct vm_area_struct *vma =  0;

	//for store data
	int i;
	int title_offset = 11;
	char* title_1 = "PAGE_TABLE\n";
	char* title_2 = "COUNTERS\n";
	for(i=0;i<11;i++)
		result[i] = title_1[i];
	char str[100];
	int ret;
	int write_count = title_offset;

	for(vma = task->mm->mmap ;vma; vma = vma -> vm_next){	
		vma_count++;
		
		for (vpage = vma->vm_start; vpage < vma->vm_end; vpage += PAGE_SIZE){

			tatol_count++;
			//if no physical adress, it will print and save as 0x000000000 to 0x000000000
			if(convert_to_phy_add(task->mm, vpage) == 0){
				no_phy_count++;

				printk(	"[VMA%d] [0x%012lx,0x%012lx] | [0x%09lx,0x%09lx] \n",
					vma_count ,
					vpage ,vpage + PAGE_SIZE,
					convert_to_phy_add(task->mm, vpage),convert_to_phy_add(task->mm, vpage)
					);
				//save virtual/physical address intervel and which VMA the page in to result[]
				ret = snprintf(str, 80,"%d\t0x%012lx\t0x%012lx\t0x%09lx\t0x%09lx\n",
								vma_count,
								vpage,vpage+PAGE_SIZE,
								convert_to_phy_add(task->mm, vpage),convert_to_phy_add(task->mm, vpage));

				for(i=0;i<ret;i++)
				{
					result[write_count] = str[i];
					write_count++;
				}

			}
			else{
				
				printk(	"[VMA%d] [0x%012lx,0x%012lx] | [0x%09lx,0x%09lx] \n",
						vma_count ,
						vpage ,vpage + PAGE_SIZE,
						convert_to_phy_add(task->mm, vpage),convert_to_phy_add(task->mm, vpage) + PAGE_SIZE
						);
				//save virtual/physical address intervel and which VMA the page in to result[]
				ret = snprintf(str, 80,"%d\t0x%012lx\t0x%012lx\t0x%09lx\t0x%09lx\n",
									vma_count,
									vpage,vpage+PAGE_SIZE,
									convert_to_phy_add(task->mm, vpage),convert_to_phy_add(task->mm, vpage)+PAGE_SIZE);
									
				for(i=0;i<ret;i++)
				{
					result[write_count] = str[i];
					write_count++;
				}
			}

		}
	}
	// save the number of pages and number of pages with no physical address
	for(i=0;i<9;i++)
	{
		result[write_count] = title_2[i];
		write_count++;
	}


	ret = snprintf(str, 10,"%d\n", no_phy_count);

	for(i=0;i<ret;i++)
	{
		result[write_count] = str[i];
		write_count++;
	}

	ret = snprintf(str, 10,"%d\n", tatol_count);

	for(i=0;i<ret;i++)
	{
		result[write_count] = str[i];
		write_count++;
	}

	printk("no_phy_count:%d\n",no_phy_count);
	printk("total_count:%d\n",tatol_count);

}

//syscall 334
SYSCALL_DEFINE1(linux_survey_TT,char*,result)
{
  	struct task_struct *task = get_current();
    vm_table(task,result);
    return 0;
}