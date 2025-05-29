using StoryToPizzaStore.Factories;
using StoryToPizzaStore.Factories.FoodFactory;

namespace StoryToPizzaStore {
    class Program {
        static void Main(string[] args) {
            // 实例化餐厅建造者
            RestaurantBuilder02 restaurantBuilder = new RestaurantBuilder02();

            // 从建造者中获取不同餐厅对象
            Restaurant bigRestaurant = restaurantBuilder.GetBigRestaurant();
            Restaurant smallRestaurant = restaurantBuilder.GetSmallRestaurant();

            // 检测餐厅对象的使用
            bigRestaurant.ShowList();
            bigRestaurant.ShowComboList();

            smallRestaurant.ShowList();
            smallRestaurant.ShowComboList();
        }
    }
}
