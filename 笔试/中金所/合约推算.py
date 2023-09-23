"""
中金所股指期货合约滚动生成按照m个近月，n个季月的规则生成。近月表示，从当前月开始连续的月份，例如当前月为8月，2个近月表示8月和9月;季月为固定的3月、6月、9月、12月。合约每月会进行交割，同时滚动生成新的合约，新生成后的合约也要满足m个近月，n个季月的规则。若月份同时满足近月和季月的要求，则认为该月为近月。给定近月数，季月数，当前年月，要求计算IZ产品未来x个月每个月新生成的合约代号。 (特别说明: 合约代号为产品名称+年份后两位+月份例如: IZ2308)
输入描述
一行记录，近月数m，季月数n，当前年月yymm，未来待计算的月份数x (m,n,yymm,x均为字符串类型)
输出描述
x行记录，第x行表示第x个月新生成的合约，若有多个按逗号分隔，若没有的话就输出“-”
"""

"""
中金所股指期货合约滚动生成按照m个近月，n个季月的规则生成。近月表示，从当前月开始连续的月份，例如当前月为8月，2个近月表示8月和9月;季月为固定的3月、6月、9月、12月。合约每月会进行交割，同时滚动生成新的合约，新生成后的合约也要满足m个近月，n个季月的规则。若月份同时满足近月和季月的要求，则认为该月为近月。给定近月数，季月数，当前年月，要求计算IZ产品未来x个月每个月新生成的合约代号。 (特别说明: 合约代号为产品名称+年份后两位+月份例如: IZ2308)
输入描述
一行记录，近月数m，季月数n，当前年月yymm，未来待计算的月份数x (m,n,yymm,x均为字符串类型)
输出描述
x行记录，第x行表示第x个月新生成的合约，若有多个按逗号分隔，若没有的话就输出“-”
"""

m, n, yymm, x = input().split()

def generate_contract_codes(m, n, yymm, x):
    near_months = []
    quarterly_months = [3, 6, 9, 12]
    current_month = int(yymm[-2:])
    current_year = int(yymm[:2])

    # Generate near months
    for i in range(int(m)):
        month = current_month + i
        year = current_year
        if month > 12:
            month -= 12
            year += 1
        near_months.append(f"IZ{year}{month:02d}")

    # Generate future months
    contract_codes = []
    for i in range(int(x)):
        month = current_month + i + int(m)
        year = current_year
        if month > 12:
            month -= 12
            year += 1
        if month in quarterly_months:
            contract_codes.append(f"IZ{year}{month:02d}")
        else:
            contract_codes.append(f"IZ{year}{month:02d}")

    return contract_codes

contract_codes = generate_contract_codes(m, n, yymm, x)
for code in contract_codes:
    print(code)