#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

float total = 0;

struct Date
{
    short unsigned int day;
    short unsigned int month;
    short unsigned int year;
};

struct Customer
{
    short unsigned int id;
    char social[5];
    char name[20];
    short unsigned int card_points;
    struct Date dob;
    int ltd;
    char address[50];
};

struct Cart
{
    char itemID[5];
    int quantity;
    int points;
    float price;
    struct Cart *next;
};

struct Item
{
    char itemID[5];
    char itemName[20];
    float price;
    int quantity;
    int points;
};

int age_calc(struct Date d)
{
    const struct tm *curr;
    time_t t;
    time(&t);

    curr = localtime(&t);
    if (curr->tm_year > d.year)
    {
        if (curr->tm_mon + 1 > d.month)
        {
            return curr->tm_year - d.year;
        }
        else if (curr->tm_mon + 1 == d.month)
        {
            if (curr->tm_mday >= d.day)
            {
                return curr->tm_year - d.year;
            }
            else
            {
                return curr->tm_year - d.year - 1;
            }
        }
        else
        {
            return curr->tm_year - d.year - 1;
        }
    }
    else
    {
        return 0;
    }
}

void createList(struct Cart **head, char itemID[5], int quantity, int points, float price)
{
    struct Cart *node = (struct Cart *)malloc(sizeof(struct Cart));
    struct Cart *temp = *head;
    strcpy(node->itemID, itemID);
    node->quantity = quantity;
    node->points = points;
    node->price = price;
    node->next = NULL;
    if (*head == NULL)
    {
        *head = node;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
}

void print(struct Customer *temp)
{
    printf("\nCustomer %hu\n", temp->id);
    printf("Social ID: %s\n", temp->social);
    printf("Name: %s\n", temp->name);
    printf("Card Points: %hu\n", temp->card_points);
    printf("DOB: %hu-%hu-%hu\n", temp->dob.day, temp->dob.month, temp->dob.year);
    printf("Address: %s\n", temp->address);
}

void item_print(struct Item *Itemp)
{
    printf("\nItem ID: %s\n", Itemp->itemID);
    printf("Item Name: %s\n", Itemp->itemName);
    printf("Price: %f\n", Itemp->price);
    printf("Quantity: %d\n", Itemp->quantity);
    printf("Points: %d\n", Itemp->points);
}

void removeCustomerLtd()
{
    int k = time(NULL);
    FILE *cust_read = fopen("customer.bin", "rb");
    FILE *temp_write = fopen("temp.bin", "wb");
    struct Customer temp;
    while (fread(&temp, sizeof(struct Customer), 1, cust_read))
    {
        if (k - temp.ltd <= 31556952)
            fwrite(&temp, sizeof(struct Customer), 1, temp_write);
    }
    fclose(cust_read);
    fclose(temp_write);
    remove("customer.bin");
    rename("temp.bin", "customer.bin");
}

int checkPresSenior(struct Customer temp)
{
    FILE *read_disc = fopen("discount_list.bin", "rb");
    struct Customer temp_temp;
    int count = 0;
    while (fread(&temp_temp, sizeof(struct Customer), 1, read_disc))
    {
        if (age_calc(temp_temp.dob) > 60)
        {
            count++;
        }
        if (!strcmp(temp_temp.social, temp.social))
        {
            fclose(read_disc);
            return count;
        }
    }
    fclose(read_disc);
    return 0;
}

int checkPres(struct Customer temp)
{
    FILE *read_disc = fopen("discount_list.bin", "rb");
    struct Customer temp_temp;
    int count = 0;
    while (fread(&temp_temp, sizeof(struct Customer), 1, read_disc))
    {
        count++;
        if (!strcmp(temp_temp.social, temp.social))
        {
            fclose(read_disc);
            return count;
        }
    }
    fclose(read_disc);
    return 0;
}

int finalCheckout(struct Cart *head)
{
    total = 0;
    int points = 0;
    struct Cart *ptr = head;
    while (ptr)
    {
        printf("\nItem ID: %s", ptr->itemID);
        printf("\nQuantity: %d", ptr->quantity);
        printf("\nPrice: %f", ptr->price);
        printf("\nPoints: %d", ptr->points);
        total = total + (ptr->quantity * ptr->price);
        points = points + ptr->points;
        ptr = ptr->next;
        printf("\n");
    }
    return points;
}

//**INT MAIN**

int main()
{
    removeCustomerLtd();
    FILE *cust_out = fopen("customer.bin", "ab");
    FILE *cust_read = fopen("customer.bin", "rb");
    int n;
    int choice;
    struct Customer temp;
    printf("\n1.Customer Login\n2.Staff Login\n3.Manager Login\n");
    scanf("%d", &choice);

    //Customers*

    if (choice == 1)
    {
        int flag = 0;
        char socialID[5];
        printf("\nEnter social security number: ");
        getchar();
        scanf("%s", socialID);
        while (!feof(cust_read))
        {
            fread(&temp, sizeof(struct Customer), 1, cust_read);
            if (!strcmp(temp.social, socialID))
            {
                printf("\nWelcome, to Amazon %s", temp.name);
                print(&temp);
                flag++;
                break;
            }
            if (feof(cust_read))
            {
                break;
            }
        }
        if (!flag)
        {
            printf("\nNo match found! Please enroll as a new user.");
            printf("Customer %d\n", temp.id + 1);
            temp.id = temp.id + 1;
            printf("Social ID: ");
            getchar();
            scanf("%s", temp.social);
            printf("Name: ");
            getchar();
            scanf("%19[^\n]", temp.name);
            // printf("Card Points: ");
            // scanf("%hu", &temp.card_points);
            temp.card_points = 0;
            printf("DOB: ");
            scanf("%hu%hu%hu", &temp.dob.day, &temp.dob.month, &temp.dob.year);
            printf("Address: ");
            getchar();
            scanf("%49[^\n]", temp.address);
            temp.ltd = time(NULL);
            //fwrite(&temp, sizeof(struct Customer), 1, cust_out);

            //Shopping Card mandate:

            printf("\nTo continue to use our services you have to buy our Amazon Shopping Card worth 50 Rupees, press 1 to continue or 0 to cancel: ");
            scanf("%d", &choice);
            if (choice)
            {
                printf("\n1.UPI\n2.Amazon Pay\n");
                scanf("%d", &choice);
                printf("\nEnter Account Pin: ");
                scanf("%d", &choice);
                printf("\nThank You, for using Amazon.");
                fwrite(&temp, sizeof(struct Customer), 1, cust_out);
                print(&temp);
            } //(fixed)BUG: if a customer relogins without buying shopping card he will get entry.
            else
            {
                printf("\nHope to see you back soon.");
                return 1;
            }
        }
        printf("\nWhat are you looking for?\n1.Shopping\n2.Address change\n3.Exit\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            //implementing linked list for cart fucntionality
            struct Cart *head = NULL;
            choice = 1;
            while (choice)
            {
                printf("\n1.Add to cart\n2.View cart\n3.Checkout\n4.Exit");
                scanf("%d", &choice);
                if (choice == 2)
                {
                    if (!head)
                    {
                        printf("\nCart Empty");
                    }
                    else
                    {
                        struct Cart *ptr;
                        ptr = head;
                        while (ptr)
                        {
                            printf("\nItem ID: %s   Quantity: %d", ptr->itemID, ptr->quantity);
                            printf("\n\n");
                            ptr = ptr->next;
                        }
                        // free(ptr);
                    }
                }

                else if (choice == 3)
                {
                    if (!head)
                    {
                        printf("\nCart is Empty");
                    }
                    else
                    {
                        //payment system here
                        int cust_points;
                        cust_points = finalCheckout(head);
                        temp.card_points += cust_points;
                        if (temp.card_points >= 1000)
                        {
                            FILE *points_out = fopen("discount_list.bin", "ab");
                            if (!checkPres(temp))
                            {
                                fwrite(&temp, sizeof(struct Customer), 1, points_out);
                                fclose(points_out);
                            }
                        }
                        int disc_flag_10 = 0; //0 -> no discount 1 -> 10% discount
                        int disc_flag_15 = 0; //0 -> no discount 1 -> 15% discount
                        int redeemed = 0;
                        time_t t;
                        time(&t);
                        const struct tm *curr = localtime(&t);
                        if (age_calc(temp.dob) > 60)
                        {
                            printf("\n>60");
                            struct Date d;
                            FILE *date_read = fopen("discount_date_15.bin", "rb");
                            fread(&d, sizeof(struct Date), 1, date_read);
                            fclose(date_read);
                            int senior_count = checkPresSenior(temp);
                            if (senior_count && senior_count <= 5)
                            {
                                if (curr->tm_year + 1900 > d.year)
                                {
                                    disc_flag_10 = 1;
                                }
                                else if (curr->tm_year + 1900 == d.year)
                                {
                                    if (curr->tm_mon + 1 > d.month)
                                    {
                                        disc_flag_10 = 1;
                                    }
                                    else if (curr->tm_mon == d.month)
                                    {
                                        if (curr->tm_mday >= d.day)
                                        {
                                            disc_flag_10 = 1;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            printf("\n<60");
                            int count = checkPres(temp);
                            // printf("\nCount: %d",count);
                            struct Date d;
                            FILE *date_read = fopen("discount_date.bin", "rb");
                            fread(&d, sizeof(struct Date), 1, date_read);
                            fclose(date_read);
                            printf("\n%d %d %d", curr->tm_mday, curr->tm_mon + 1, curr->tm_year + 1900);
                            if (count && count <= 10)
                            {
                                if (curr->tm_year + 1900 > d.year)
                                {
                                    disc_flag_10 = 1;
                                }
                                else if (curr->tm_year + 1900 == d.year)
                                {
                                    if (curr->tm_mon + 1 > d.month)
                                    {
                                        disc_flag_10 = 1;
                                    }
                                    else if (curr->tm_mon == d.month)
                                    {
                                        if (curr->tm_mday >= d.day)
                                        {
                                            disc_flag_10 = 1;
                                        }
                                    }
                                }
                            }
                            else if (count <= 20 && count > 10)
                            {
                                if (curr->tm_year + 1900 > d.year)
                                {
                                    if (d.month != 12)
                                    {
                                        disc_flag_10 = 1;
                                    }
                                    else if ((curr->tm_year + 1900) - d.year == 1 && curr->tm_mday >= d.day)
                                    {
                                        disc_flag_10 = 1;
                                    }
                                }
                                else if (curr->tm_year + 1900 == d.year && curr->tm_mon + 1 - d.month == 1 && curr->tm_mday >= d.day)
                                {
                                    disc_flag_10 = 1;
                                }
                            }
                        }
                        //implement points system and checkcust_out system
                        //remember to decrease stock
                        //point addition system here
                        //if redeemed, set redeemed = 1 card_points -= 1000
                        //update the card_points after current payment before coming here

                        if (disc_flag_15)
                        {
                            printf("\nYou are eligible for a discount of 15%%, do you accept?(0/1): ");
                            scanf("%d", &choice);
                            if (choice)
                            {
                                total = total - (0.15 * total);
                                redeemed = 1;
                                temp.card_points -= 1000;
                            }
                        }

                        else if (disc_flag_10)
                        {
                            printf("\nYou are eligible for a 10%% discount, do you accept?(0/1): ");
                            scanf("%d", &choice);
                            if (choice)
                            {
                                total = total - (0.1 * total);
                                redeemed = 1;
                                temp.card_points -= 1000;
                            }
                        }
                        printf("\nYour total is: %f", total);
                        printf("\nEnter your card number: ");
                        scanf("%d", &choice);
                        printf("\nThank you for shopping with Amazon.");
                        temp.ltd = time(NULL);
                        return 0;
                        //program ends cause transaction successful

                        FILE *temp_out = fopen("temp.bin", "wb");
                        fseek(cust_read, 0, SEEK_SET);
                        struct Customer ctemp;
                        while (fread(&ctemp, sizeof(struct Customer), 1, cust_read))
                        {
                            if (!(strcmp(ctemp.social, temp.social)))
                            {
                                fwrite(&temp, sizeof(struct Customer), 1, temp_out);
                            }
                            else
                            {
                                fwrite(&ctemp, sizeof(struct Customer), 1, temp_out);
                            }
                        }
                        fclose(temp_out);
                        fclose(cust_read);
                        remove("customer.bin");
                        rename("temp.bin", "customer.bin");
                        cust_read = fopen("customer.bin", "rb");

                        if (redeemed && temp.card_points < 1000)
                        {
                            FILE *points_in = fopen("discount_list.bin", "rb");
                            FILE *temp_out = fopen("temp.bin", "wb");
                            struct Customer temp_temp;
                            while (fread(&temp_temp, sizeof(struct Customer), 1, points_in))
                            {
                                if (!strcmp(temp_temp.social, temp.social))
                                    ;
                                fwrite(&temp_temp, sizeof(struct Customer), 1, temp_out);
                            }
                            fclose(points_in);
                            fclose(temp_out);
                            remove("discount_list.bin");
                            rename("temp.bin", "discount_list.bin");
                        }
                    }
                }

                //add to cart

                else if (choice == 1)
                {
                    FILE *item_read = fopen("Item.bin", "rb");
                    struct Item Itemp;
                    while ((fread(&Itemp, sizeof(struct Item), 1, item_read)))
                    {

                        item_print(&Itemp);
                        printf("\n");
                    }
                    printf("\n\n");
                    choice = 1;
                    while (choice)
                    {
                        char itemID[5];
                        printf("\nEnter Item ID of item you want: ");
                        getchar();
                        scanf("%s", itemID);
                        printf("\nYou entered : %s", itemID);
                        fseek(item_read, 0, SEEK_SET);
                        int flag = 1;
                        while (fread(&Itemp, sizeof(struct Item), 1, item_read))
                        {

                            if (!strcmp(Itemp.itemID, itemID))
                            {
                                flag = 0;
                                int quantity;
                                printf("\nEnter quantity: ");
                                scanf("%d", &quantity);
                                if (quantity > Itemp.quantity)
                                {
                                    printf("\nOut of stock");
                                    break;
                                }
                                else
                                {
                                    // int flag=1;
                                    Itemp.quantity = Itemp.quantity - quantity;

                                    // printf("\nFlag: %d",flag);
                                    createList(&head, Itemp.itemID, quantity, Itemp.points, Itemp.price);
                                    fseek(item_read, 0, SEEK_SET);
                                    FILE *temp_out = fopen("temp.bin", "wb");
                                    struct Item temp;
                                    while (fread(&temp, sizeof(struct Item), 1, item_read))
                                    {
                                        if (!strcmp(Itemp.itemID, temp.itemID))
                                        {
                                            fwrite(&Itemp, sizeof(struct Item), 1, temp_out);
                                        }
                                        else
                                        {
                                            fwrite(&temp, sizeof(struct Item), 1, temp_out);
                                        }
                                    }
                                    fclose(item_read);
                                    fclose(temp_out);
                                    remove("Item.bin");
                                    rename("temp.bin", "Item.bin");
                                    item_read = fopen("Item.bin", "rb");
                                    printf("\nItem added");
                                    break;
                                }
                            }
                            // else
                            // {
                            //     printf("\nNo such item found.");
                            //     break;
                            // }
                        }
                        if (flag)
                        {
                            printf("\nNo such item found");
                        }
                        printf("\nDo you want to enter more items?: ");
                        scanf("%d", &choice);
                    }
                }

                else if (choice == 4)
                {
                    break;
                }
                printf("\nGo back to main menu?: ");
                scanf("%d", &choice);
            }
        }
        else if (choice == 2)
        {
            printf("\nYour current Address is : %s", temp.address);
            printf("\nEnter new address: ");
            getchar();
            scanf("%49[^\n]", temp.address); //(fixed)ekhane ki abar fwrite korte hobe?
            // FILE *cust_write = fopen("customer.bin", "wb");
            FILE *temp_out = fopen("temp.bin", "wb");
            fseek(cust_read, 0, SEEK_SET);
            struct Customer ctemp;
            while (fread(&ctemp, sizeof(struct Customer), 1, cust_read))
            {
                if (!strcmp(ctemp.social, temp.social))
                {
                    fwrite(&temp, sizeof(struct Customer), 1, temp_out);
                }
                else
                {
                    fwrite(&ctemp, sizeof(struct Customer), 1, temp_out);
                }
            }
            fclose(cust_read);
            fclose(temp_out);
            remove("customer.bin");
            rename("temp.bin", "customer.bin");
            cust_read = fopen("customer.bin", "rb");
        }
        else
        {
            return 1;
        }
    }

    //Staff members

    else if (choice == 2)
    {
        int pass = 1234;
        int pass_check;
        printf("\nEnter Passcode: ");
        scanf("%d", &pass_check);
        if (pass_check == pass)
        {
            struct Item Itemp;
            FILE *item_read = fopen("Item.bin", "rb");

            printf("\nWelcome to Amazon Staff Portal.\n");
            printf("\n1.Show Item Details\n2.Edit Item Details\n3.Add Item Details\n");
            scanf("%d", &choice);
            if (choice == 3)
            {
                FILE *item_out = fopen("Item.bin", "ab");

                choice = 1;
                while (choice == 1)
                {
                    fseek(item_read, 0, SEEK_SET);
                    int flag = 0;

                    char itemID_check[5];
                    printf("\nEnter Item ID: ");
                    getchar();
                    scanf("%s", itemID_check);
                    while (!feof(item_read))
                    {
                        fread(&Itemp, sizeof(struct Item), 1, item_read);
                        if (!strcmp(Itemp.itemID, itemID_check))
                        {
                            printf("\nItem Already Exists.");
                            flag++;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        printf("\nEnter Details for Item ID: %s", itemID_check);
                        strcpy(Itemp.itemID, itemID_check);
                        printf("\nEnter Item Name: ");
                        getchar();
                        scanf("%20[^\n]", Itemp.itemName);
                        printf("\nEnter Price: ");
                        scanf("%f", &Itemp.price);
                        printf("\nEnter Quantity: ");
                        scanf("%d", &Itemp.quantity);
                        printf("\nEnter points: ");
                        scanf("%d", &Itemp.points);
                        fwrite(&Itemp, sizeof(struct Item), 1, item_out);
                    }
                    printf("\nDo you want to enter more?(0/1): ");
                    scanf("%d", &choice);
                }
                fclose(item_out);
            }

            else if (choice == 1)
            {
                fseek(item_read, 0, SEEK_SET);
                while (fread(&Itemp, sizeof(struct Item), 1, item_read))
                {

                    item_print(&Itemp);
                    printf("\n");
                }
            }

            else if (choice == 2)
            {
                int flag = 0;
                char itemID_check[5];
                printf("\nEnter Item ID which you want to edit: ");
                getchar();
                scanf("%s", itemID_check);
                fseek(item_read, 0, SEEK_SET);
                FILE *i_out = fopen("temp.bin", "wb");
                while (fread(&Itemp, sizeof(struct Item), 1, item_read))
                {
                    if (!strcmp(Itemp.itemID, itemID_check))
                    {
                        printf("\nMatch Found\n");
                        // FILE *item_write = fopen("Item.bin", "wb");
                        flag++;
                        printf("\n1.Change Name\n2.Change Price\n3.Change Quantity\n4.Change Points\n");
                        scanf("%d", &choice);
                        // item_write = item_read;
                        // fseek(item_write, -1, SEEK_CUR);
                        // char itemName[20];
                        // float price;
                        // int quantity;
                        // int points;
                        switch (choice)
                        { //fix replacing system

                        case 1:

                            printf("\nEnter new name: ");
                            getchar();
                            scanf("%20[^\n]", Itemp.itemName);
                            // fwrite(&Itemp, sizeof(struct Item), 1, item_write);
                            break;
                        case 2:

                            printf("\nEnter new price: ");
                            scanf("%f", &Itemp.price);
                            // fwrite(&Itemp, sizeof(struct Item), 1, item_write);
                            break;
                        case 3:

                            printf("\nEnter new quantity: ");
                            scanf("%d", &Itemp.quantity);
                            // fwrite(&Itemp, sizeof(struct Item), 1, item_write);
                            break;
                        case 4:

                            printf("\nEnter new point: ");
                            scanf("%d", &Itemp.points);
                            // fwrite(&Itemp, sizeof(struct Item), 1, item_write);
                            break;
                        }
                        // fclose(item_write);

                        // break;
                    }
                    fwrite(&Itemp, sizeof(struct Item), 1, i_out);
                }
                fclose(item_read);
                fclose(i_out);
                remove("Item.bin");
                rename("temp.bin", "Item.bin");
                item_read = fopen("Item.bin", "rb");
                if (!flag)
                {
                    printf("\nNo such Item found.");
                }
            }
        }
        else
        {
            printf("\nWrong Passcode");
            return 1;
        }
    }

    //**Manager**

    else if (choice == 3)
    {
        int pass = 4321;
        int check_pass;
        printf("\nEnter pass: ");
        scanf("%d", &check_pass);

        if (check_pass == pass)
        {
            printf("\nWelcome to Amazon Manager Service\n");
            printf("\n1.10%% discount\n2.15%% discount");
            scanf("%d", &choice);
            struct Date d;
            if (choice == 1)
            {

                printf("\nEnter date to execute offer: ");
                scanf("%hu%hu%hu", &d.day, &d.month, &d.year);
                FILE *date_out = fopen("discount_date.bin", "wb");
                fwrite(&d, sizeof(struct Date), 1, date_out);
                fclose(date_out);
            }
            else if (choice == 2)
            {
                // struct Date d;
                printf("\nEnter date to execute offer: ");
                scanf("%hu%hu%hu", &d.day, &d.month, &d.year);
                FILE *date_out_15 = fopen("discount_date_15.bin", "wb");
                fwrite(&d, sizeof(struct Date), 1, date_out_15);
                fclose(date_out_15);
            }
        }
    }

    fclose(cust_out);
    fclose(cust_read);

    return 0;
}

//decrease item stock after one buys it
//warn if item out of stock