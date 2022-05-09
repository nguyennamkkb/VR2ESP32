String hangdoi_Front(){ // lay vi tri hien tai 
	//xong
	int len=0;
	while(hang_doi[hang_doi_front] == "" && len <= hang_doi_tong){
	    hang_doi_front = (hang_doi_front + 1) % hang_doi_tong;
		hang_doi_sothietbidangdoi = hang_doi_sothietbidangdoi - 1;
		len++;
	}
	return  hang_doi[hang_doi_front];
}